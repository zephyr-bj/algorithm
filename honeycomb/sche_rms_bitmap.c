#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include <stdatomic.h>

#define MAX_TASKS 3
#define MAX_PRIO  8
#define TICK_USEC 100000

/* ===================== */
/* Task State            */
/* ===================== */

typedef enum {
    TASK_IDLE = 0,
    TASK_READY,
    TASK_RUNNING,
    TASK_PREEMPTED,
    TASK_DONE
} task_state_t;

/* ===================== */
/* Task Control Block    */
/* ===================== */

typedef struct task {
    int id;
    int period;
    int exec_time;

    atomic_int remaining_time;
    atomic_int next_release;
    atomic_int state;

    int priority;

    struct task* next;
    pthread_t thread;

} task_t;

/* ===================== */
/* Runqueue + Bitmap     */
/* ===================== */

typedef uint32_t prio_bitmap_t;

typedef struct {
    task_t* head;
    task_t* tail;
} runqueue_t;

static runqueue_t runqueues[MAX_PRIO];
static prio_bitmap_t ready_bitmap = 0;

static inline void set_bit(int p) {
    ready_bitmap |= (1u << p);
}

static inline void clear_bit(int p) {
    ready_bitmap &= ~(1u << p);
}

static inline int highest_prio(prio_bitmap_t bm) {
    return __builtin_ctz(bm);
}

/* ===================== */
/* Global                */
/* ===================== */

task_t tasks[MAX_TASKS];
task_t* current_task = NULL;

atomic_int tick_count = 0;

/* ===================== */
/* Work Simulation       */
/* ===================== */

void do_work_chunk(int id) {
    printf("    [Task %d] working...\n", id);
    usleep(20000);
}

/* ===================== */
/* Task Thread           */
/* ===================== */

void* task_thread(void* arg) {
    task_t* t = (task_t*)arg;

    while (1) {

        while (atomic_load_explicit(&t->state, memory_order_acquire) != TASK_RUNNING) {
            usleep(1000);
        }

        while (1) {
            do_work_chunk(t->id);

            int st = atomic_load_explicit(&t->state, memory_order_acquire);

            if (st != TASK_RUNNING) {
                if (st == TASK_PREEMPTED) {
                    printf("    [Task %d] preempted\n", t->id);
                }
                break;
            }
        }
    }
}

/* ===================== */
/* Runqueue Ops (O(1))   */
/* ===================== */

void enqueue_task(task_t* t) {
    int p = t->priority;
    runqueue_t* rq = &runqueues[p];

    t->next = NULL;

    if (!rq->head) {
        rq->head = rq->tail = t;
        set_bit(p);
    } else {
        rq->tail->next = t;
        rq->tail = t;
    }
}

task_t* dequeue_task(int p) {
    runqueue_t* rq = &runqueues[p];

    task_t* t = rq->head;
    if (!t) return NULL;

    rq->head = t->next;

    if (!rq->head) {
        rq->tail = NULL;
        clear_bit(p);
    }

    return t;
}

task_t* pick_next_task() {
    if (ready_bitmap == 0)
        return NULL;

    int p = highest_prio(ready_bitmap);
    return dequeue_task(p);
}

/* ===================== */
/* RMS Priority Mapping  */
/* ===================== */

int rms_priority(int period) {
    if (period <= 5) return 0;
    if (period <= 10) return 1;
    return 2;
}

/* ===================== */
/* Scheduler             */
/* ===================== */

void release_tasks(int now) {
    for (int i = 0; i < MAX_TASKS; i++) {
        int nr = atomic_load_explicit(&tasks[i].next_release, memory_order_relaxed);

        if (now == nr) {
            atomic_store_explicit(&tasks[i].remaining_time,
                                  tasks[i].exec_time,
                                  memory_order_relaxed);

            atomic_store_explicit(&tasks[i].state,
                                  TASK_READY,
                                  memory_order_release);

            atomic_store_explicit(&tasks[i].next_release,
                                  nr + tasks[i].period,
                                  memory_order_relaxed);

            enqueue_task(&tasks[i]);

            printf("[time %2d] Task %d released\n", now, tasks[i].id);
        }
    }
}

void schedule(int now) {

    release_tasks(now);

    task_t* next = pick_next_task();

    if (next != current_task) {

        if (current_task) {
            int rem = atomic_load_explicit(&current_task->remaining_time, memory_order_relaxed);

            if (rem > 0) {
                atomic_store_explicit(&current_task->state,
                                      TASK_PREEMPTED,
                                      memory_order_release);

                enqueue_task(current_task);
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

/* ===================== */
/* Timer Thread          */
/* ===================== */

void* timer_thread(void* arg) {
    while (1) {
        usleep(TICK_USEC);
        atomic_fetch_add_explicit(&tick_count, 1, memory_order_relaxed);
    }
}

/* ===================== */
/* Scheduler Thread      */
/* ===================== */

void* scheduler_thread(void* arg) {
    int last_tick = -1;

    schedule(0); // initial release

    while (1) {
        int now = atomic_load_explicit(&tick_count, memory_order_acquire);

        if (now != last_tick) {
            last_tick = now;
            schedule(now);
        }

        if (now > 50) break;
    }
}

/* ===================== */
/* Main                  */
/* ===================== */

int main() {

    tasks[0] = (task_t){ .id=1, .period=5,  .exec_time=2 };
    tasks[1] = (task_t){ .id=2, .period=10, .exec_time=3 };
    tasks[2] = (task_t){ .id=3, .period=20, .exec_time=5 };

    for (int i = 0; i < MAX_TASKS; i++) {
        tasks[i].priority = rms_priority(tasks[i].period);

        atomic_init(&tasks[i].remaining_time, 0);
        atomic_init(&tasks[i].next_release, 0);
        atomic_init(&tasks[i].state, TASK_IDLE);

        pthread_create(&tasks[i].thread, NULL, task_thread, &tasks[i]);
    }

    pthread_t timer_tid, sched_tid;

    pthread_create(&timer_tid, NULL, timer_thread, NULL);
    pthread_create(&sched_tid, NULL, scheduler_thread, NULL);

    pthread_join(sched_tid, NULL);

    return 0;
}
