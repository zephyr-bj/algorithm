#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdatomic.h>

#define MAX_TASKS 3
#define TICK_USEC 100000

typedef struct {
    int id;
    int period;
    int execution_time;
    int remaining_time;
    int next_release;

    pthread_t thread;
    atomic_int should_run;
} task_t;

task_t tasks[MAX_TASKS];

int tick_count = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t tick_cv = PTHREAD_COND_INITIALIZER;

task_t* current_task = NULL;

/* ===================== */
/* Signal-based preemption */
/* ===================== */

void preempt_handler(int sig) {
    (void)sig;
    // Nothing heavy here — just interruption point
}

/* ===================== */
/* Simulated Work (chunked) */
/* ===================== */

void do_work_chunk(int task_id) {
    printf("    [Task %d] working chunk...\n", task_id);
    usleep(20000);  // 20ms chunk
}

/* ===================== */
/* Task Thread */
/* ===================== */

void* task_thread(void* arg) {
    task_t* t = (task_t*)arg;

    signal(SIGUSR1, preempt_handler);

    while (1) {
        // Wait until scheduler allows running
        while (!atomic_load(&t->should_run)) {
            usleep(1000);
        }

        // Run in small chunks → allows preemption points
        do {
            do_work_chunk(t->id);

            // Check if preempted
            if (!atomic_load(&t->should_run)) {
                if (&t->remaining_time > 0) {
                    printf("    [Task %d] preempted\n", t->id);
                }
                break;
            }

        } while (1);
    }
    return NULL;
}

/* ===================== */
/* RMS Logic */
/* ===================== */

void release_tasks(int time) {
    for (int i = 0; i < MAX_TASKS; i++) {
        if (time == tasks[i].next_release) {
            tasks[i].remaining_time = tasks[i].execution_time;
            tasks[i].next_release += tasks[i].period;

            printf("[time %2d] Task %d released\n", time, tasks[i].id);
        }
    }
}

task_t* pick_task() {
    task_t* best = NULL;

    for (int i = 0; i < MAX_TASKS; i++) {
        if (tasks[i].remaining_time > 0) {
            if (!best || tasks[i].period < best->period) {
                best = &tasks[i];
            }
        }
    }
    return best;
}

/* ===================== */
/* Timer Thread */
/* ===================== */

void* timer_thread(void* arg) {
    while (1) {
        usleep(TICK_USEC);

        pthread_mutex_lock(&lock);
        tick_count++;
        pthread_cond_signal(&tick_cv);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

/* ===================== */
/* Scheduler */
/* ===================== */

void* scheduler_thread(void* arg) {
    release_tasks(0);  // fix time 0 issue

    while (tick_count < 50) {
        pthread_mutex_lock(&lock);
        pthread_cond_wait(&tick_cv, &lock);
        int now = tick_count;
        pthread_mutex_unlock(&lock);

        release_tasks(now);

        task_t* next = pick_task();

        if (next != current_task) {

            if (current_task) {
                atomic_store(&current_task->should_run, 0);
                pthread_kill(current_task->thread, SIGUSR1);
            }

            if (next) {
                printf("[time %2d] Switch to Task %d\n", now, next->id);
                atomic_store(&next->should_run, 1);
            } else {
                printf("[time %2d] Idle\n", now);
            }

            current_task = next;
        }

        // Account execution
        if (current_task) {
            current_task->remaining_time--;

            if (current_task->remaining_time == 0) {
                printf("[time %2d] Task %d completed\n", now, current_task->id);
                atomic_store(&current_task->should_run, 0);
                current_task = NULL;
            }
        }
    }
    return NULL;
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
        atomic_init(&tasks[i].should_run, 0);
        pthread_create(&tasks[i].thread, NULL, task_thread, &tasks[i]);
    }

    pthread_create(&timer_tid, NULL, timer_thread, NULL);
    pthread_create(&sched_tid, NULL, scheduler_thread, NULL);

    pthread_join(sched_tid, NULL);

    return 0;
}
