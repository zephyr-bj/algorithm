#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*
advantages rms over edf
1. Predictability and "Stability" during Overload (e.g. a interrupt burst):
   edf: one over limit trigger many deadline miss
   rms: gracefully degrades to set of high priority tasks
2. rms is cheaper, do not need sort
3. better jitter control: Because the highest-frequency task 
   always has the highest priority in RMS, its latency jitter 
   (the variation in when it starts) is nearly zero. 
   In EDF, a low-frequency task might occasionally have 
   an earlier absolute deadline than a high-frequency task, 
   causing the high-frequency task to be delayed and increasing its jitter.
*/

// Use a 64-bit integer as our priority bitmap (supports 64 priority levels)
typedef unsigned long long bitmap_t;

typedef void (*TaskJob)(int id);

typedef struct Task {
    int id;
    int exec_time;
    int period;
    int priority;    // Static: 0 is highest, 63 is lowest
    int rem_time;
    int abs_deadline;
    TaskJob job;
} Task;

// --- Global Kernel Structures ---
bitmap_t ready_bitmap = 0;
Task* priority_table[64] = {NULL}; // Maps priority level -> Task pointer

typedef struct DeltaNode {
    Task* task;
    int delta;
    struct DeltaNode* next;
} DeltaNode;

DeltaNode* waiting_list = NULL;

// --- Bitmap Operations (O(1)) ---

void mark_ready(int priority) {
    ready_bitmap |= (1ULL << priority);
}

void clear_ready(int priority) {
    ready_bitmap &= ~(1ULL << priority);
}

int get_highest_priority() {
    if (ready_bitmap == 0) return -1;
    // __builtin_ctzll finds the number of trailing zeros (the index of the first '1' bit)
    // This is a hardware-accelerated O(1) operation on most modern CPUs.
    return __builtin_ctzll(ready_bitmap);
}

// --- Delta List (Arrivals) ---
void insert_waiting(Task* t, int delay) {
    if (delay < 0) delay = 0;
    DeltaNode **curr = &waiting_list;
    while (*curr && delay >= (*curr)->delta) {
        delay -= (*curr)->delta;
        curr = &((*curr)->next);
    }
    DeltaNode* node = malloc(sizeof(DeltaNode));
    node->task = t;
    node->delta = delay;
    node->next = *curr;
    if (node->next) node->next->delta -= delay;
    *curr = node;
}

// --- RMS Kernel ---

void run_rms_bitmap_scheduler(int total_ticks) {
    Task* current_task = NULL;

    printf("Tick | Event      | Task | Bitmap (Hex) | Action\n");
    printf("---------------------------------------------------\n");

    for (int t = 0; t < total_ticks; t++) {
        // 1. Process Arrivals (O(1) check of Delta Head)
        if (waiting_list) waiting_list->delta--;
        while (waiting_list && waiting_list->delta <= 0) {
            Task* arriving = waiting_list->task;
            arriving->rem_time = arriving->exec_time;
            arriving->abs_deadline = t + arriving->period;
            
            mark_ready(arriving->priority); // O(1)
            
            DeltaNode* temp = waiting_list;
            waiting_list = waiting_list->next;
            free(temp);
            printf("%4d | ARRIVAL    | T%d   | 0x%llx      | Marked Priority %d\n", 
                   t, arriving->id, ready_bitmap, arriving->priority);
        }

        // 2. Selection (O(1) using FFS)
        int top_prio = get_highest_priority();
        
        // Preemption Logic
        if (current_task != NULL && top_prio != -1 && top_prio < current_task->priority) {
            printf("%4d | PREEMPT    | T%d   | 0x%llx      | Higher Prio T%d Ready\n", 
                   t, current_task->id, ready_bitmap, priority_table[top_prio]->id);
            mark_ready(current_task->priority);
            current_task = NULL;
        }

        if (current_task == NULL && top_prio != -1) {
            current_task = priority_table[top_prio];
            clear_ready(top_prio);
        }

        // 3. Execution
        printf("%4d | ", t);
        if (current_task) {
            printf("RUN        | T%d   | 0x%llx      | Executing...\n", current_task->id, ready_bitmap);
            current_task->rem_time--;

            if (current_task->rem_time <= 0) {
                int next_arrival = current_task->period - (t % current_task->period) - 1;
                insert_waiting(current_task, next_arrival);
                current_task = NULL;
            }
        } else {
            printf("IDLE       | ---  | 0x%llx      | CPU Sleep\n", ready_bitmap);
        }
    }
}

int main() {
    // Priority 0 is highest. In RMS, shorter period = higher priority.
    Task t1 = {1, 2, 5, 0, 0, 0, NULL}; // Period 5 -> Prio 0
    Task t2 = {2, 3, 12, 1, 0, 0, NULL}; // Period 12 -> Prio 1

    priority_table[0] = &t1;
    priority_table[1] = &t2;

    insert_waiting(&t1, 0);
    insert_waiting(&t2, 0);

    run_rms_bitmap_scheduler(25);

    return 0;
}
