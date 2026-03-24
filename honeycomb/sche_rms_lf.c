#include <stdatomic.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#define MAX_TASKS 3
#define TICK_USEC 100000

typedef enum {
    TASK_IDLE = 0,
    TASK_READY,
    TASK_RUNNING,
    TASK_PREEMPTED,
    TASK_DONE
} task_state_t;

typedef struct {
    int id;
    int period;
    int execution_time;

    atomic_int remaining_time;
    atomic_int next_release;

    atomic_int state;        // task_state_t
    pthread_t thread;
} task_t;

task_t tasks[MAX_TASKS];

/* ===================== */
/* Simulated Work (chunked) */
/* ===================== */

void do_work_chunk(int task_id) {
    printf("    [Task %d] working chunk...\n", task_id);
    usleep(20000);  // 20ms chunk
}

// Task Thread (Lock-Free, Correct Ordering)
void* task_thread(void* arg) {
    task_t* t = (task_t*)arg;

    while (1) {

        // Wait until RUNNING
        while (atomic_load_explicit(&t->state, memory_order_acquire) != TASK_RUNNING) {
            usleep(1000);
        }

        // Execute in chunks
        while (1) {

            do_work_chunk(t->id);

            int state = atomic_load_explicit(&t->state, memory_order_acquire);

            if (state != TASK_RUNNING) {
                if (state == TASK_PREEMPTED) {
                    printf("    [Task %d] preempted\n", t->id);
                }
                break;
            }
        }
    }
}

// Scheduler
task_t* current_task = NULL;

void schedule(int now) {

    // Release tasks (scheduler owns next_release)
    for (int i = 0; i < MAX_TASKS; i++) {
        int nr = atomic_load_explicit(&tasks[i].next_release, memory_order_relaxed);

        if (now == nr) {
            atomic_store_explicit(&tasks[i].remaining_time,
                                  tasks[i].execution_time,
                                  memory_order_relaxed);

            atomic_store_explicit(&tasks[i].state,
                                  TASK_READY,
                                  memory_order_release);

            atomic_store_explicit(&tasks[i].next_release,
                                  nr + tasks[i].period,
                                  memory_order_relaxed);

            printf("[time %2d] Task %d released\n", now, tasks[i].id);
        }
    }

    // Pick next (RMS)
    task_t* next = NULL;

    for (int i = 0; i < MAX_TASKS; i++) {
        int rem = atomic_load_explicit(&tasks[i].remaining_time, memory_order_relaxed);

        if (rem > 0) {
            if (!next || tasks[i].period < next->period) {
                next = &tasks[i];
            }
        }
    }

    // Context switch decision
    if (next != current_task) {

        if (current_task) {
            int rem = atomic_load_explicit(&current_task->remaining_time, memory_order_relaxed);

            if (rem > 0) {
                atomic_store_explicit(&current_task->state,
                                      TASK_PREEMPTED,
                                      memory_order_release);
            }
        }

        if (next) {
            atomic_store_explicit(&next->state,
                                  TASK_RUNNING,
                                  memory_order_release);

            printf("[time %2d] Switch to Task %d\n", now, next->id);
        } else {
            printf("[time %2d] Idle\n", now);
        }

        current_task = next;
    }

    // Execute 1 tick worth of work
    if (current_task) {
        int rem = atomic_load_explicit(&current_task->remaining_time, memory_order_relaxed);

        rem--;

        atomic_store_explicit(&current_task->remaining_time,
                              rem,
                              memory_order_relaxed);

        if (rem == 0) {
            atomic_store_explicit(&current_task->state,
                                  TASK_DONE,
                                  memory_order_release);

            printf("[time %2d] Task %d completed\n", now, current_task->id);

            current_task = NULL;
        }
    }
}

// Timer Thread (Lock-Free Trigger)
atomic_int tick_count = 0;

void* timer_thread(void* arg) {
    while (1) {
        usleep(TICK_USEC);

        atomic_fetch_add_explicit(&tick_count, 1, memory_order_relaxed);
    }
}

// Scheduler Loop (Polling, Lock-Free)
void* scheduler_thread(void* arg) {
    int last_tick = -1;

    schedule(0);  // initial release

    while (1) {
        int now = atomic_load_explicit(&tick_count, memory_order_acquire);

        if (now != last_tick) {
            last_tick = now;
            schedule(now);
        }
    }
}

/* ===================== */
/* Main */
/* ===================== */

int main() {
    pthread_t timer_tid, sched_tid;

    tasks[0] = (task_t){ .id=1, .period=5,  .execution_time=2, .next_release=0 };
    tasks[1] = (task_t){ .id=2, .period=10, .execution_time=3, .next_release=0 };
    tasks[2] = (task_t){ .id=3, .period=20, .execution_time=5, .next_release=0 };

    for (int i = 0; i < MAX_TASKS; i++) {
        atomic_init(&tasks[i].state, 0);
        pthread_create(&tasks[i].thread, NULL, task_thread, &tasks[i]);
    }

    pthread_create(&timer_tid, NULL, timer_thread, NULL);
    pthread_create(&sched_tid, NULL, scheduler_thread, NULL);

    pthread_join(sched_tid, NULL);

    return 0;
}
