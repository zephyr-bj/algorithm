#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Delta List for Waiting queue
// Min Heap for Ready queue
#include <stdio.h>
#include <stdlib.h>

typedef void (*TaskJob)(int id);

typedef struct Task {
    int id;
    int exec_time;
    int period;
    int deadline;
    int rem_time;
    int abs_deadline;
    bool is_periodic; // New: True for repeating, False for one-shot
    TaskJob job;
} Task;

// --- Global Kernel Structures ---
Task* ready_heap[100];
int heap_size = 0;

typedef struct DeltaNode {
    Task* task;
    int delta;
    struct DeltaNode* next;
} DeltaNode;

DeltaNode* waiting_list = NULL;

// --- Helper Functions (Heap & Delta) ---
void swap(int i, int j) { Task* t = ready_heap[i]; ready_heap[i] = ready_heap[j]; ready_heap[j] = t; }

void push_ready(Task* t) {
    int i = heap_size++;
    ready_heap[i] = t;
    while (i > 0 && ready_heap[i]->abs_deadline < ready_heap[(i-1)/2]->abs_deadline) {
        swap(i, (i-1)/2); i = (i-1)/2;
    }
}

Task* pop_ready() {
    if (heap_size == 0) return NULL;
    Task* top = ready_heap[0];
    ready_heap[0] = ready_heap[--heap_size];
    int i = 0;
    while (i * 2 + 1 < heap_size) {
        int child = i * 2 + 1;
        if (child + 1 < heap_size && ready_heap[child+1]->abs_deadline < ready_heap[child]->abs_deadline) child++;
        if (ready_heap[i]->abs_deadline <= ready_heap[child]->abs_deadline) break;
        swap(i, child); i = child;
    }
    return top;
}

void insert_waiting(Task* t, int delay) {
    DeltaNode **curr = &waiting_list;
    while (*curr && delay >= (*curr)->delta) { delay -= (*curr)->delta; curr = &((*curr)->next); }
    DeltaNode* node = malloc(sizeof(DeltaNode));
    node->task = t; node->delta = delay; node->next = *curr;
    if (node->next) node->next->delta -= delay;
    *curr = node;
}

// --- The Scheduler Function ---
void run_scheduler(int total_ticks) {
    Task* current_task = NULL;

    printf("Tick | Event   | Task | Job Execution\n");
    printf("--------------------------------------------\n");

    for (int t = 0; t < total_ticks; t++) {
        // 1. Process Arrivals (Delta List -> Ready Heap)
        if (waiting_list) waiting_list->delta--;
        while (waiting_list && waiting_list->delta <= 0) {
            Task* arriving = waiting_list->task;
            arriving->rem_time = arriving->exec_time;
            arriving->abs_deadline = t + arriving->deadline;
            push_ready(arriving);

            DeltaNode* temp = waiting_list;
            waiting_list = waiting_list->next;
            free(temp);
        }

        // 2. Preemption Check
        // If a task in the heap has an earlier deadline than the current one, swap!
        if (current_task != NULL && heap_size > 0) {
            if (ready_heap[0]->abs_deadline < current_task->abs_deadline) {
                printf("%4d | PREEMPT | T%d   | Swapping T%d for T%d\n", t, current_task->id, current_task->id, ready_heap[0]->id);
                push_ready(current_task);
                current_task = NULL;
            }
        }

        // 3. Selection
        if (current_task == NULL) {
            current_task = pop_ready();
        }

        // 4. Execution
        printf("%4d | ", t);
        if (current_task) {
            printf("RUN     | T%d   |", current_task->id);
            current_task->job(current_task->id);
            current_task->rem_time--;

            // Check for completion
            if (current_task->rem_time == 0) {
                printf(" (DONE)");
                if (current_task->is_periodic) {
                    int next_arrival = current_task->period - (t % current_task->period) - 1;
                    insert_waiting(current_task, next_arrival);
                }
                current_task = NULL;
            }
        } else {
            printf("IDLE    | ---  | CPU Sleeping...");
        }
        printf("\n");
    }
}

// --- Application Code ---
void sensor_job(int id) { printf(" [Sampling Data]"); }
void comms_job(int id)  { printf(" [Sending Packet]"); }
void alert_job(int id)  { printf(" [!!! ONE-SHOT ALERT !!!]"); }

int main() {
    Task t1 = {1, 2, 10, 4, 0, 0, true, sensor_job}; // High urgency (D=4)
    Task t2 = {2, 3, 15, 15, 0, 0, true, comms_job}; // Low urgency (D=15)
    Task t3 = {99, 1, 0, 2, 0, 0, false, alert_job};

    // Set initial arrivals
    insert_waiting(&t1, 0);
    insert_waiting(&t2, 0);
    insert_waiting(&t3, 12);

    run_scheduler(30);

    return 0;
}
