#include <iostream>
#include <vector>
#include <memory>
#include <mutex>
#include <functional>
#include <thread>
#include <chrono>

// --- 1. Task Definition ---
struct Task {
    int id;
    int exec_time;
    uint64_t abs_deadline; // Absolute tick when this task must finish
    std::function<void(int)> job;
};

// Node for our linked-list buckets inside the wheel
struct TaskNode {
    Task task;
    std::shared_ptr<TaskNode> next;
    TaskNode(const Task& t) : task(t), next(nullptr) {}
};

// --- 2. Hierarchical Two-Level Timer Wheel ---
class EDFTimerWheel {
private:
    static constexpr int TVL1_BITS = 6;                  // Level 0: 64 slots (Near)
    static constexpr int TVL2_BITS = 6;                  // Level 1: 64 slots (Far)
    static constexpr int TVL1_SIZE = 1 << TVL1_BITS;     // 64
    static constexpr int TVL2_SIZE = 1 << TVL2_BITS;     // 64
    
    static constexpr int TVL1_MASK = TVL1_SIZE - 1;
    static constexpr int TVL2_MASK = TVL2_SIZE - 1;

    // The two tiers of our wheel buckets
    std::shared_ptr<TaskNode> tv1[TVL1_SIZE] = {nullptr}; // Spans 0 to 63 ticks out
    std::shared_ptr<TaskNode> tv2[TVL2_SIZE] = {nullptr}; // Spans 64 to 4095 ticks out

    uint64_t current_tick = 0;
    std::mutex scheduler_mutex; // Mutex used to safely protect multi-level cascading

    // Internal helper to add a node to a specific bucket list
    void add_node_to_list(std::shared_ptr<TaskNode>* bucket, std::shared_ptr<TaskNode> node) {
        node->next = *bucket;
        *bucket = node;
    }

    // Cascades tasks from Level 1 down to Level 0 when a Level 0 rollover occurs
    void cascade_wheel(int level_index) {
        std::shared_ptr<TaskNode> curr = tv2[level_index];
        tv2[level_index] = nullptr; // Clear the Far bucket

        while (curr) {
            std::shared_ptr<TaskNode> next_node = curr->next;
            curr->next = nullptr;

            // Re-insert into Level 0 based on its remaining lifetime
            uint64_t idx = curr->task.abs_deadline - current_tick;
            int l1_slot = (current_tick + idx) & TVL1_MASK;
            add_node_to_list(&tv1[l1_slot], curr);

            curr = next_node;
        }
        std::cout << "[Kernel] Cascade complete for Level 1 Slot [" << level_index << "]\n";
    }

public:
    // --- Push Operation ---
    void push_task(const Task& task) {
        std::lock_guard<std::mutex> lock(scheduler_mutex);

        // Dynamic check: how far away is this absolute deadline from right now?
        uint64_t idx = task.abs_deadline - current_tick;
        auto new_node = std::make_shared<TaskNode>(task);

        if (idx < TVL1_SIZE) {
            // Fits in the Near Wheel (Level 0)
            int slot = task.abs_deadline & TVL1_MASK;
            add_node_to_list(&tv1[slot], new_node);
            std::cout << "[Kernel] Task " << task.id << " pushed to LVL0 Slot [" << slot << "]\n";
        } 
        else if (idx < (TVL1_SIZE * TVL2_SIZE)) {
            // Too far for Level 0, goes into the Far Wheel (Level 1)
            int slot = (task.abs_deadline >> TVL1_BITS) & TVL2_MASK;
            add_node_to_list(&tv2[slot], new_node);
            std::cout << "[Kernel] Task " << task.id << " pushed to LVL1 Slot [" << slot << "]\n";
        } 
        else {
            std::cerr << "[Kernel Error] Deadline too far out for 2-Level Wheel capacity!\n";
        }
    }

    // --- Pop/Tick Operation ---
    // Advances the clock tick and fetches the list of tasks whose deadlines are due EXACTLY now
    bool tick_and_pop(std::vector<Task>& ready_tasks) {
        std::lock_guard<std::mutex> lock(scheduler_mutex);

        // Calculate current slot index for Level 0
        int slot = current_tick & TVL1_MASK;

        // If Level 0 wraps back around to 0, it means 64 ticks have passed.
        // We must cascade tasks from Level 1 down into Level 0.
        if (slot == 0 && current_tick > 0) {
            int l1_slot = (current_tick >> TVL1_BITS) & TVL2_MASK;
            cascade_wheel(l1_slot);
        }

        // Extract any tasks scheduled for this exact tick bucket
        std::shared_ptr<TaskNode> curr = tv1[slot];
        tv1[slot] = nullptr; // Flush the bucket slot

        while (curr) {
            ready_tasks.push_back(curr->task);
            curr = curr->next;
        }

        current_tick++; // Tick the clock forward
        return !ready_tasks.empty();
    }

    uint64_t get_current_tick() const { return current_tick; }
};

// --- 3. Simulation Target ---
void dummy_job(int id) {
    std::cout << " -> Executing Task " << id << "\n";
}

int main() {
    EDFTimerWheel scheduler;

    // Let's create tasks with distinct absolute deadlines
    // Notice Task 3 has a far-out deadline that will land in Level 1
    scheduler.push_task(Task{1, 1, 4,  dummy_job});  // Tick 4  (LVL0)
    scheduler.push_task(Task{2, 1, 12, dummy_job});  // Tick 12 (LVL0)
    scheduler.push_task(Task{3, 1, 75, dummy_job});  // Tick 75 (LVL1: requires cascading!)

    std::cout << "\n--- Starting Core Execution Ticks ---\n";

    // Run clock ticks 0 to 80
    for (int t = 0; t <= 80; t++) {
        std::vector<Task> executable_now;
        
        if (scheduler.tick_and_pop(executable_now)) {
            std::cout << "[Tick " << t << "] Dispatching matching EDF deadlines:\n";
            for (const auto& task : executable_now) {
                std::cout << "   [Target Match] Absolute Deadline: " << task.abs_deadline;
                task.job(task.id);
            }
        }

        // Simulate 10ms passage of real-world time per system tick
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}
