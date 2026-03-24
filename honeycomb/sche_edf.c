#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_TASKS 64
#define QUEUE_SIZE 128

//---------------------------------------------
// Task structure
//---------------------------------------------
typedef struct {
    int id;
    int period;
    int execution_time;
    int remaining_time;
    int release_time;
    int absolute_deadline;
} task_t;

//---------------------------------------------
// Lock-free MPSC ring buffer
//---------------------------------------------
typedef struct {
    task_t buffer[QUEUE_SIZE];
    atomic_uint head;  // producer writes
    atomic_uint tail;  // consumer reads
} lf_queue_t;

lf_queue_t ready_queue;

//---------------------------------------------
// Queue operations (MPSC lock-free)
//---------------------------------------------
bool enqueue(lf_queue_t *q, task_t t) {
    unsigned int head = atomic_load_explicit(&q->head, memory_order_relaxed);

    while (1) {
        unsigned int tail = atomic_load_explicit(&q->tail, memory_order_acquire);
        if ((head - tail) >= QUEUE_SIZE) {
            return false; // full
        }

        if (atomic_compare_exchange_weak_explicit(
                &q->head, &head, head + 1,
                memory_order_acq_rel, memory_order_relaxed)) {
            q->buffer[head % QUEUE_SIZE] = t;
            return true;
        }
    }
}

bool dequeue(lf_queue_t *q, task_t *out) {
    unsigned int tail = atomic_load_explicit(&q->tail, memory_order_relaxed);
    unsigned int head = atomic_load_explicit(&q->head, memory_order_acquire);

    if (tail == head)
        return false;

    *out = q->buffer[tail % QUEUE_SIZE];

    atomic_store_explicit(&q->tail, tail + 1, memory_order_release);
    return true;
}

//---------------------------------------------
// Global simulation state
//---------------------------------------------
task_t task_set[MAX_TASKS];
int num_tasks = 0;

// active jobs (local to scheduler → no locks needed)
task_t active[MAX_TASKS];

//---------------------------------------------
// Add periodic task
//---------------------------------------------
void add_task(int id, int period, int exec_time) {
    task_set[num_tasks++] = (task_t){
        .id = id,
        .period = period,
        .execution_time = exec_time,
        .remaining_time = 0,
        .release_time = 0,
        .absolute_deadline = 0
    };
}

//---------------------------------------------
// Release jobs (producer side)
//---------------------------------------------
void release_tasks(int now) {
    for (int i = 0; i < num_tasks; i++) {
        if (now % task_set[i].period == 0) {
            task_t job = task_set[i];
            job.remaining_time = job.execution_time;
            job.release_time = now;
            job.absolute_deadline = now + job.period;

            enqueue(&ready_queue, job);
        }
    }
}

//---------------------------------------------
// Pick EDF task (earliest deadline)
//---------------------------------------------
int pick_edf(task_t *tasks, int count) {
    int best = -1;
    for (int i = 0; i < count; i++) {
        if (tasks[i].remaining_time <= 0)
            continue;

        if (best == -1 ||
            tasks[i].absolute_deadline < tasks[best].absolute_deadline) {
            best = i;
        }
    }
    return best;
}

//---------------------------------------------
// Scheduler simulation
//---------------------------------------------
void run_simulation(int duration) {
    int active_count = 0;

    for (int t = 0; t < duration; t++) {

        // Release new jobs (producer)
        release_tasks(t);

        // Drain queue into active list
        task_t job;
        while (dequeue(&ready_queue, &job)) {
            if (active_count < MAX_TASKS) {
                active[active_count++] = job;
            }
        }
        printf("active_count = %d\n", active_count);

        // Pick EDF task
        int idx = pick_edf(active, active_count);

        if (idx == -1) {
            printf("[time %d] IDLE\n", t);
            continue;
        }

        task_t *task = &active[idx];

        printf("[time %d] Run Task %d (deadline=%d, remaining=%d)\n",
               t, task->id, task->absolute_deadline, task->remaining_time);

        // Execute 1 tick
        task->remaining_time--;

        // Deadline miss detection
        if (t > task->absolute_deadline) {
            printf("  !!! Deadline MISS for Task %d\n", task->id);
        }
    }
}

//---------------------------------------------
// Init queue
//---------------------------------------------
void init_queue(lf_queue_t *q) {
    atomic_init(&q->head, 0);
    atomic_init(&q->tail, 0);
}

//---------------------------------------------
// Main
//---------------------------------------------
int main() {
    init_queue(&ready_queue);

    // Example task set
    add_task(1, 5, 2);
    add_task(2, 7, 3);
    add_task(3, 10, 1);

    run_simulation(50);

    return 0;
}
