#include <iostream>
#include <vector>
#include <queue>
#include <atomic>
#include <functional>
#include <chrono>
#include <thread>

// --- 1. Task Definition ---
struct Task {
    int id;
    int exec_time;
    int abs_deadline; // The key for EDF (Earliest Deadline First)
    std::function<void(int)> job;

    // The task with the EARLIEST deadline must be at the top.
    bool operator>(const Task& other) const {
        return abs_deadline > other.abs_deadline;
    }
};

// Custom wrapper logic for priority_queue to enforce min-heap
struct CompareTask {
    bool operator()(const Task& a, const Task& b) const {
        return a > b; // Returns true if 'a' has a later deadline than 'b'
    }
};

// --- 2. Hardware-Level Spinlock Implementation ---
class Spinlock {
private:
    std::atomic_flag lock_flag = ATOMIC_FLAG_INIT; 

public:
    void lock() {
        // test_and_set() atomically sets the flag to true and returns the OLD value.
        // It loops (spins) as long as the old value was true (meaning someone else holds the lock).
        while (lock_flag.test_and_set(std::memory_order_acquire)) {
            // In a real OS/hardware environment, you would insert a compiler hint here 
            // like __builtin_ia32_pause() or asm("pause") to save CPU power.
        }
    }

    void unlock() {
        lock_flag.clear(std::memory_order_release);
    }
};

// --- 3. Thread-Safe EDF Ready Queue ---
class EDFScheduler {
private:
    std::priority_queue<Task, std::vector<Task>, CompareTask> ready_queue;
    Spinlock lock; // Protects the shared priority_queue

public:
    // Push operation: Safe to call from any thread or core context
    void push_task(const Task& task) {
        lock.lock();
        ready_queue.push(task);
        std::cout << "[Kernel] Task " << task.id 
                  << " pushed (Abs Deadline: " << task.abs_deadline << ")\n";
        lock.unlock();
    }

    // Pop operation: Safely retrieves and removes the highest-priority (earliest deadline) task
    bool pop_task(Task& out_task) {
        lock.lock();
        if (ready_queue.empty()) {
            lock.unlock();
            return false;
        }
        
        out_task = ready_queue.top();
        ready_queue.pop();
        lock.unlock();
        return true;
    }
    
    bool is_empty() {
        lock.lock();
        bool empty = ready_queue.empty();
        lock.unlock();
        return empty;
    }
};

// --- 4. Simulation / Testing ---
void dummy_job(int id) {
    std::cout << " -> Executing Task " << id << " on Core " 
              << std::this_thread::get_id() << "\n";
}
int main() {
    EDFScheduler scheduler;
    Task Tasks[] = {
        {1, 2, 20, dummy_job},
        {2, 3, 50, dummy_job},
        {3, 1, 35, dummy_job},
        {4, 1, 10, dummy_job}
    };
    std::vector<std::thread>producers;
    int prod_cnt = 4;
    for(int i = 0; i < prod_cnt; i++) {
        std::thread producer([&](int id){
            int task_cnt = 10;
            int interval = 15;
            for (int j = 0; j < task_cnt; j++) {
                scheduler.push_task(Tasks[id]);
                std::this_thread::sleep_for(std::chrono::milliseconds(interval+id));
            }
        }, i);
        producers.push_back(std::move(producer));
    }

    // Dispatch tasks
    Task current_run;
    int cons_task_cnt = 35;
    while (cons_task_cnt > 0) {
        if (!scheduler.is_empty() && scheduler.pop_task(current_run)) {
            std::cout << "[Run Tick] Selected Task " << current_run.id
                      << " (Deadline: " << current_run.abs_deadline << ")";
            current_run.job(current_run.id);
            cons_task_cnt--;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    for(int i = 0; i < prod_cnt; i++) {
        producers.back().join();
        producers.pop_back();
    }

    return 0;
}
/*
int main() {
    EDFScheduler scheduler;

    std::thread producer1([&scheduler]() {
        int task_cnt = 10;
        for (int i = 0; i < task_cnt; i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            scheduler.push_task(Task{3, 1, 15, dummy_job});
        }
    });

    std::thread producer2([&scheduler]() {
        int task_cnt = 10;
        for (int i = 0; i < task_cnt; i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            scheduler.push_task(Task{1, 2, 20, dummy_job});
        }
    });

    std::thread producer3([&scheduler]() {
        int task_cnt = 20;
        for (int i = 0; i < task_cnt; i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            scheduler.push_task(Task{2, 3, 50, dummy_job});
        }
    });

    std::cout << "\n--- Scheduler dispatching tasks based on EDF order ---\n";
    
    Task current_run;
    int done_cnt = 20;
    while (done_cnt > 0) {
        if (!scheduler.is_empty() && scheduler.pop_task(current_run)) {
            std::cout << "[Run Tick] Selected Task " << current_run.id 
                      << " (Deadline: " << current_run.abs_deadline << ")";
            current_run.job(current_run.id);
            done_cnt--;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    producer1.join();
    producer2.join();
    producer3.join();

    return 0;
}*/
