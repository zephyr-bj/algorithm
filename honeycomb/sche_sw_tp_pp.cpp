#include <iostream>
#include <queue>
#include <functional>
#include <chrono>
#include <thread>
#include <condition_variable>
#include <atomic>
#include <vector>

class PriorityScheduler {
public:
    using Clock = std::chrono::steady_clock;
    using TimePoint = Clock::time_point;
    using Duration = Clock::duration;
    using TaskFunc = std::function<void()>;

    PriorityScheduler() : stop_flag(false) {
        worker = std::thread([this]() { run(); });
    }

    ~PriorityScheduler() {
        stop();
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

    // Immediate task
    void schedule(TaskFunc func, int priority = 0) {
        schedule_at(Clock::now(), std::move(func), Duration::zero(), priority);
    }

    // Delayed task
    void schedule_after(Duration delay, TaskFunc func, int priority = 0) {
        schedule_at(Clock::now() + delay, std::move(func), Duration::zero(), priority);
    }

    // Periodic task
    void schedule_every(Duration interval, TaskFunc func, int priority = 0) {
        schedule_at(Clock::now() + interval, std::move(func), interval, priority);
    }

private:
    struct Task {
        TimePoint next_run;
        TaskFunc func;
        Duration interval;
        int priority;
        size_t id;
    };

    struct TimerCompare {
        bool operator()(const Task& a, const Task& b) const {
            return a.next_run > b.next_run;  // min-heap
        }
    };

    struct ReadyCompare {
        bool operator()(const Task& a, const Task& b) const {
            if (a.priority == b.priority)
                return a.id > b.id; // FIFO for same priority
            return a.priority < b.priority; // max-heap by priority
        }
    };

    std::priority_queue<Task, std::vector<Task>, TimerCompare> timer_queue;
    std::priority_queue<Task, std::vector<Task>, ReadyCompare> ready_queue;

    std::mutex mtx;
    std::condition_variable cv;
    std::thread worker;
    std::atomic<bool> stop_flag;
    std::atomic<size_t> id_gen{0};

    void schedule_at(TimePoint tp, TaskFunc func, Duration interval, int priority) {
        std::lock_guard<std::mutex> lock(mtx);
        timer_queue.push(Task{tp, std::move(func), interval, priority, id_gen++});
        cv.notify_all();
    }

    void run() {
        std::unique_lock<std::mutex> lock(mtx);

        while (!stop_flag) {

            auto now = Clock::now();

            // Move expired timers to ready queue
            while (!timer_queue.empty() && timer_queue.top().next_run <= now) {
                ready_queue.push(timer_queue.top());
                timer_queue.pop();
            }

            // If ready tasks exist → execute highest priority
            if (!ready_queue.empty()) {
                Task task = ready_queue.top();
                ready_queue.pop();

                lock.unlock();
                task.func();
                lock.lock();

                // Reschedule periodic
                if (task.interval != Duration::zero()) {
                    task.next_run += task.interval; // avoid drift
                    timer_queue.push(task);
                }

                continue;
            }

            // No ready tasks → wait for next timer
            if (!timer_queue.empty()) {
                cv.wait_until(lock, timer_queue.top().next_run);
            } else {
                cv.wait(lock);
            }
        }
    }
};

int main() {
    PriorityScheduler scheduler;

    scheduler.schedule([] {
        std::cout << "Low priority\n";
    }, 1);

    scheduler.schedule([] {
        std::cout << "High priority\n";
    }, 10);

    scheduler.schedule_every(std::chrono::seconds(1), [] {
        std::cout << "Periodic mid priority\n";
    }, 5);

    std::this_thread::sleep_for(std::chrono::seconds(3));
    scheduler.stop();
}

