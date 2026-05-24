#include <iostream>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <cstdint>
#include <memory>
#include <functional>
#include <thread>

// Class representing a Task
struct Task {
    int id;
    int period; // RMS rule: Shorter period -> Higher Priority
    std::function<void()> execute;
};

class RMScheduler {
private:
    // 32-bit bitmap representing ready priority levels.
    // Bit 31 = Highest Priority, Bit 0 = Lowest Priority.
    uint32_t ready_bitmap = 0;

    // Array of queues for each priority level (0 to 31)
    std::queue<std::shared_ptr<Task>> ready_queues[32];

    std::mutex sched_mutex;
    std::condition_variable wake_dispatcher;
    bool shutdown = false;

    // Helper to find the highest priority bit set (O(1) using compiler intrinsic)
    int get_highest_priority_level() const {
        if (ready_bitmap == 0) return -1;
        // __builtin_clz counts leading zeros. 
        // e.g., if bit 31 is set, leading zeros = 0 -> priority = 31.
        return 31 - __builtin_clz(ready_bitmap);
    }

public:
    // Push a task into its designated priority queue
    void push_task(int priority, std::shared_ptr<Task> task) {
        if (priority < 0 || priority > 31) {
            std::cerr << "Error: Priority must be between 0 and 31.\n";
            return;
        }

        {
            std::lock_guard<std::mutex> lock(sched_mutex);
            
            // Step 1: Insert task into the specific priority queue
            ready_queues[priority].push(task);
            
            // Step 2: Set the corresponding bit in the bitmap
            ready_bitmap |= (1U << priority);
        }
        
        // Step 3: Signal the scheduler dispatcher thread
        wake_dispatcher.notify_one();
    }

    // Pop the highest priority task currently available
    std::shared_ptr<Task> pop_task() {
        std::unique_lock<std::mutex> lock(sched_mutex);

        // Wait until there is a task or shutdown is initiated
        wake_dispatcher.wait(lock, [this]() { 
            return ready_bitmap != 0 || shutdown; 
        });

        if (shutdown && ready_bitmap == 0) {
            return nullptr;
        }

        // Find the highest priority level with an active task
        int highest_pri = get_highest_priority_level();
        
        if (highest_pri == -1) return nullptr;

        // Retrieve the task
        auto task = ready_queues[highest_pri].front();
        ready_queues[highest_pri].pop();

        // If that specific priority queue is now empty, clear its bit in the bitmap
        if (ready_queues[highest_pri].empty()) {
            ready_bitmap &= ~(1U << highest_pri);
        }

        return task;
    }

    void stop() {
        {
            std::lock_guard<std::mutex> lock(sched_mutex);
            shutdown = true;
        }
        wake_dispatcher.notify_all();
    }
};

// --- Demo Usage ---
int main() {
    RMScheduler scheduler;

    // Create a few dummy tasks
    // According to RMS: Task 1 (shortest period) gets highest priority
    auto task1 = std::make_shared<Task>(Task{1, 10, []() { std::cout << "Executing Task 1 (High Priority)\n"; }});
    auto task2 = std::make_shared<Task>(Task{2, 30, []() { std::cout << "Executing Task 2 (Mid Priority)\n"; }});
    auto task3 = std::make_shared<Task>(Task{3, 100, []() { std::cout << "Executing Task 3 (Low Priority)\n"; }});

    // Simulated Dispatcher/CPU Loop
    std::thread dispatcher([&scheduler]() {
        while (true) {
            auto task = scheduler.pop_task();
            if (!task) break; // Exit loop on shutdown
            
            task->execute();
        }
        std::cout << "Dispatcher shutting down.\n";
    });

    // Simulate scheduling tasks arriving out of order
    std::cout << "Pushing low priority task 3...\n";
    scheduler.push_task(5, task3);  // Priority 5

    std::cout << "Pushing high priority task 1...\n";
    scheduler.push_task(31, task1); // Priority 31

    std::cout << "Pushing mid priority task 2...\n";
    scheduler.push_task(15, task2); // Priority 15

    // Let the dispatcher finish processing
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    scheduler.stop();
    dispatcher.join();

    return 0;
}
