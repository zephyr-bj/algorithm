#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define WHEEL_SIZE 64  // Bits for Level 0
#define TVR_BITS 6     // 2^6 = 64
#define TVR_SIZE (1 << TVR_BITS)
#define TVN_BITS 6
#define TVN_SIZE (1 << TVN_BITS)

typedef void (*TaskJob)(int id);

typedef struct Task {
    int id;
    int exec_time;
    int period;
    int deadline;
    int rem_time;
    int abs_deadline;
    TaskJob job;
    bool is_periodic;
} Task;

// Timer Wheel structures
typedef struct TimerNode {
    Task* task;
    struct TimerNode* next;
} TimerNode;

typedef struct {
    unsigned long current_tick;
    TimerNode* tv0[TVR_SIZE]; // Level 0: Near
    TimerNode* tv1[TVN_SIZE]; // Level 1: Far
} TimerWheel;

TimerWheel wheel = {0};

// --- Ready Queue (Min-Heap) ---
Task* ready_heap[100];
int heap_size = 0;

void push_ready(Task* t) {
    int i = heap_size++;
    ready_heap[i] = t;
    while (i > 0 && ready_heap[i]->abs_deadline < ready_heap[(i-1)/2]->abs_deadline) {
        Task* tmp = ready_heap[i]; ready_heap[i] = ready_heap[(i-1)/2]; ready_heap[(i-1)/2] = tmp;
        i = (i-1)/2;
    }
}

Task* pop_ready() {
    if (heap_size == 0) return NULL;
    Task* top = ready_heap[0];
    ready_heap[0] = ready_heap[--heap_size];
    // Simple heapify down
    int i = 0;
    while (i * 2 + 1 < heap_size) {
        int child = i * 2 + 1;
        if (child + 1 < heap_size && ready_heap[child+1]->abs_deadline < ready_heap[child]->abs_deadline) child++;
        if (ready_heap[i]->abs_deadline <= ready_heap[child]->abs_deadline) break;
        Task* tmp = ready_heap[i]; ready_heap[i] = ready_heap[child]; ready_heap[child] = tmp;
        i = child;
    }
    return top;
}

// --- Timer Wheel Functions ---

void add_to_wheel(Task* t, unsigned long timeout) {
    unsigned long expires = wheel.current_tick + timeout;
    unsigned long idx = expires - wheel.current_tick;
    TimerNode* node = malloc(sizeof(TimerNode));
    node->task = t;

    if (idx < TVR_SIZE) {
        int i = expires & (TVR_SIZE - 1);
        node->next = wheel.tv0[i];
        wheel.tv0[i] = node;
    } else {
        // Simple 2nd level mapping
        int i = (expires >> TVR_BITS) & (TVN_SIZE - 1);
        node->next = wheel.tv1[i];
        wheel.tv1[i] = node;
    }
}

void cascade(int wheel_idx) {
    TimerNode* curr = wheel.tv1[wheel_idx];
    wheel.tv1[wheel_idx] = NULL;
    while (curr) {
        TimerNode* next = curr->next;
        // Re-insert into Level 0
        int i = (wheel.current_tick + (curr->task->period)) & (TVR_SIZE - 1); // Simplification for demo
        curr->next = wheel.tv0[i];
        wheel.tv0[i] = curr;
        curr = next;
    }
}

void run_timer_wheel_edf(int ticks) {
    Task* current = NULL;

    for (int t = 0; t < ticks; t++) {
        wheel.current_tick = t;
        int ring_idx = t & (TVR_SIZE - 1);

        // 1. Cascade if Level 0 wrapped around
        if (ring_idx == 0 && t > 0) {
            cascade((t >> TVR_BITS) & (TVN_SIZE - 1));
        }

        // 2. Process Current Slot
        TimerNode* curr = wheel.tv0[ring_idx];
        wheel.tv0[ring_idx] = NULL;
        while (curr) {
            Task* t_ready = curr->task;
            t_ready->rem_time = t_ready->exec_time;
            t_ready->abs_deadline = t + t_ready->deadline;
            push_ready(t_ready);
            TimerNode* tmp = curr; curr = curr->next; free(tmp);
        }

        // 3. Preempt & Select (EDF)
        if (current && heap_size > 0 && ready_heap[0]->abs_deadline < current->abs_deadline) {
            push_ready(current); current = NULL;
        }
        if (!current) current = pop_ready();

        // 4. Execute
        printf("%03d | ", t);
        if (current) {
            printf("RUN T%d (Rem:%d, DL:%d)", current->id, current->rem_time, current->abs_deadline);
            current->rem_time--;
            if (current->rem_time == 0) {
                if (current->is_periodic) add_to_wheel(current, current->period);
                current = NULL;
            }
        } else printf("IDLE");
        printf("\n");
    }
}

void job(int id) {} // Dummy

int main() {
    Task t1 = {1, 2, 10, 10, 0, 0, job, true};
    Task t2 = {2, 5, 80, 80, 0, 0, job, true}; // This will eventually land in Level 1

    add_to_wheel(&t1, 0);
    add_to_wheel(&t2, 0);

    run_timer_wheel_edf(100);
    return 0;
}
