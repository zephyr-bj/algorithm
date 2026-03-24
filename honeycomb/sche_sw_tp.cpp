#include <iostream>
#include <queue>
#include <functional>
#include <chrono>
#include <thread>
#include <condition_variable>
#include <atomic>
#include <memory>

// compile with pthread: g++ sche_sw_tp.cpp -pthread -o sche

// single worker, time priority

class TaskScheduler {
public:
    using Clock = std::chrono::steady_clock;
    using TimePoint = Clock::time_point;
    using Duration = Clock::duration;
    using TaskFunc = std::function<void()>;

    TaskScheduler() : stop_flag(false) {
        worker = std::thread([this]() { run(); });
    }

    ~TaskScheduler() {
        stop();
    }

    // Schedule a task to run immediately (one-shot)
    void schedule(TaskFunc func) {
        schedule_at(Clock::now(), std::move(func), Duration::zero());
    }

    // Schedule a task to run after a delay (one-shot)
    void schedule_after(Duration delay, TaskFunc func) {
        schedule_at(Clock::now() + delay, std::move(func), Duration::zero());
    }

    // Schedule periodic task
    void schedule_every(Duration interval, TaskFunc func) {
        schedule_at(Clock::now() + interval, std::move(func), interval);
    }

    void stop() {
        {
            std::lock_guard<std::mutex> lock(mtx);
            stop_flag = true;
        }
        cv.notify_all();
        if (worker.joinable())
            worker.join();
    }

private:
    struct Task {
        TimePoint next_run;
        TaskFunc func;
        Duration interval;   // zero = one-shot
        size_t id;

        Task(TimePoint tp, TaskFunc tf, Duration period, size_t index):
            next_run(tp), func(tf), interval(period), id(index){
        }
        // we need the two 'const' in this definition
        bool operator>(const Task& other) const {
            return next_run > other.next_run;
        }
    };

    std::priority_queue<Task, std::vector<Task>, std::greater<Task>> task_queue;
    std::mutex mtx;
    std::condition_variable cv;
    std::thread worker;
    std::atomic<bool> stop_flag;
    std::atomic<size_t> id_gen{0};

    void schedule_at(TimePoint tp, TaskFunc func, Duration interval) {
        std::lock_guard<std::mutex> lock(mtx);
        task_queue.push(Task(tp, std::move(func), interval, id_gen++));
        cv.notify_all();
    }

    void run() {
        std::unique_lock<std::mutex> lock(mtx);

        while (!stop_flag) {
            if (task_queue.empty()) {
                cv.wait(lock);
                continue;
            }

            auto now = Clock::now();
            auto next_task = task_queue.top();

            if (next_task.next_run > now) {
                cv.wait_until(lock, next_task.next_run);
                continue;
            }

            // Pop task
            task_queue.pop();

            // Unlock while executing
            lock.unlock();
            next_task.func();
            lock.lock();

            // Reschedule if periodic
            if (next_task.interval != Duration::zero()) {
                next_task.next_run = Clock::now() + next_task.interval;
                task_queue.push(next_task);
            }
        }
    }
};

int main() {
    TaskScheduler scheduler;

    scheduler.schedule([] {
        std::cout << "Immediate task\n";
    });

    scheduler.schedule_after(std::chrono::seconds(2), [] {
        std::cout << "Delayed 2 seconds\n";
    });

    scheduler.schedule_every(std::chrono::seconds(1), [] {
        std::cout << "Periodic every 1 second\n";
    });

    std::this_thread::sleep_for(std::chrono::seconds(5));
    scheduler.stop();
}

