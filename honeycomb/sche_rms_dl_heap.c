#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef void (*TaskJob)(int id);

typedef struct Task {
    int id;
    int exec_time;
    int period;      // In RMS, Period IS the priority (Shorter P = Higher Priority)
    int deadline;    
    int rem_time;
    int abs_deadline;
    TaskJob job;
} Task;

// --- 1. MIN-HEAP FOR READY QUEUE (Keyed by Period for RMS) ---
Task* ready_heap[100];
int heap_size = 0;

void swap(int i, int j) {
    Task* temp = ready_heap[i];
    ready_heap[i] = ready_heap[j];
    ready_heap[j] = temp;
}

void push_ready(Task* t) {
    ready_heap[heap_size] = t;
    int i = heap_size++;
    // RMS CHANGE: Compare periods, not absolute deadlines
    while (i > 0 && ready_heap[i]->period < ready_heap[(i-1)/2]->period) {
        swap(i, (i-1)/2);
        i = (i-1)/2;
    }
}

Task* pop_ready() {
    if (heap_size == 0) return NULL;
    Task* top = ready_heap[0];
    ready_heap[0] = ready_heap[--heap_size];
    int i = 0;
    while (i * 2 + 1 < heap_size) {
        int child = i * 2 + 1;
        // RMS CHANGE: Compare periods
        if (child + 1 < heap_size && ready_heap[child+1]->period < ready_heap[child]->period) 
            child++;
        if (ready_heap[i]->period <= ready_heap[child]->period) break;
        swap(i, child);
        i = child;
    }
    return top;
}

// --- 2. DELTA LIST FOR WAITING QUEUE ---
typedef struct DeltaNode {
    Task* task;
    int delta;
    struct DeltaNode* next;
} DeltaNode;

DeltaNode* waiting_list = NULL;

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

// --- 3. RMS KERNEL ---

void run_rms_scheduler(int total_ticks) {
    Task* current_task = NULL;

    printf("Tick | Event      | Task | Priority (Period)\n");
    printf("--------------------------------------------\n");

    for (int t = 0; t < total_ticks; t++) {
        // A. Handle Arrivals
        if (waiting_list) waiting_list->delta--;
        while (waiting_list && waiting_list->delta <= 0) {
            Task* arriving = waiting_list->task;
            arriving->rem_time = arriving->exec_time;
            arriving->abs_deadline = t + arriving->deadline;
            
            push_ready(arriving);
            
            DeltaNode* temp = waiting_list;
            waiting_list = waiting_list->next;
            free(temp);
            printf("%4d | ARRIVAL    | T%d   | P: %d\n", t, arriving->id, arriving->period);
        }

        // B. Preemption Check (RMS: Does a newly ready task have a shorter period?)
        if (current_task && heap_size > 0) {
            if (ready_heap[0]->period < current_task->period) {
                printf("%4d | PREEMPT    | T%d   | Swapping for higher freq T%d\n", t, current_task->id, ready_heap[0]->id);
                push_ready(current_task);
                current_task = NULL;
            }
        }

        if (!current_task) current_task = pop_ready();

        // C. Execution
        printf("%4d | ", t);
        if (current_task) {
            printf("RUN        | T%d   | Executing...", current_task->id);
            current_task->rem_time--;

            // Deadline Miss Check
            if (t >= current_task->abs_deadline && current_task->rem_time > 0) {
                printf(" -> FAILED DEADLINE!");
            }

            if (current_task->rem_time <= 0) {
                int next_arrival = current_task->period - (t % current_task->period) - 1;
                insert_waiting(current_task, next_arrival);
                current_task = NULL;
            }
        } else {
            printf("IDLE       | ---  | CPU Sleep");
        }
        printf("\n");
    }
}

void dummy_job(int id) {}

int main() {
    // T1: High Frequency (Period 6) -> High Priority
    // T2: Low Frequency (Period 15) -> Low Priority
    Task t1 = {1, 2, 6, 6, 0, 0, dummy_job};
    Task t2 = {2, 4, 15, 15, 0, 0, dummy_job};
    
    insert_waiting(&t1, 0);
    insert_waiting(&t2, 0);

    run_rms_scheduler(30);

    return 0;
}
