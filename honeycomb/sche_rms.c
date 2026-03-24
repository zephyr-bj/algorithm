#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_TASKS 3
#define TICK_USEC 100000   // 100ms per tick

typedef struct {
    int id;
    int period;
    int execution_time;     // in ticks
    int remaining_time;
    int next_release;
} task_t;

task_t tasks[MAX_TASKS];

int tick_count = 0;
int need_resched = 0;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t tick_cv = PTHREAD_COND_INITIALIZER;

/* ===================== */
/* Simulated Task Work   */
/* ===================== */

void delay_task1() {
    printf("    [Task 1] working...\n");
    usleep(30000);  // 30 ms
}

void delay_task2() {
    printf("    [Task 2] working...\n");
    usleep(60000);  // 60 ms
}

void delay_task3() {
    printf("    [Task 3] working...\n");
    usleep(90000);  // 90 ms
}

void run_task(int id) {
    switch (id) {
        case 1: delay_task1(); break;
        case 2: delay_task2(); break;
        case 3: delay_task3(); break;
    }
}

/* ===================== */
/* RMS Scheduler Logic   */
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
/* Timer Thread (ISR sim)*/
/* ===================== */

void* timer_thread(void* arg) {
    while (1) {
        usleep(TICK_USEC);

        pthread_mutex_lock(&lock);
        tick_count++;
        need_resched = 1;

        pthread_cond_signal(&tick_cv);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

/* ===================== */
/* Scheduler Thread      */
/* ===================== */

void* scheduler_thread(void* arg) {
    while (tick_count < 50) {

        // real systems have an initial scheduling point independent of the timer.
        // so do not need this explicit time 0 release
        release_tasks(0);

        pthread_mutex_lock(&lock);

        while (!need_resched) {
            pthread_cond_wait(&tick_cv, &lock);
        }

        int now = tick_count;
        need_resched = 0;

        pthread_mutex_unlock(&lock);

        /* Release periodic jobs */
        release_tasks(now);

        /* Pick highest-priority task */
        task_t* current = pick_task();

        if (current) {
            printf("[time %2d] Running Task %d\n", now, current->id);

            run_task(current->id);

            current->remaining_time--;

            if (current->remaining_time == 0) {
                printf("[time %2d] Task %d completed\n", now, current->id);
            }
        } else {
            printf("[time %2d] Idle\n", now);
        }
    }
    return NULL;
}

/* ===================== */
/* Main                  */
/* ===================== */

int main() {
    pthread_t timer_tid, sched_tid;

    /* Initialize tasks (RMS priorities: smaller period = higher priority) */
    tasks[0] = (task_t){ .id=1, .period=5,  .execution_time=2, .remaining_time=0, .next_release=0 };
    tasks[1] = (task_t){ .id=2, .period=10, .execution_time=3, .remaining_time=0, .next_release=0 };
    tasks[2] = (task_t){ .id=3, .period=20, .execution_time=5, .remaining_time=0, .next_release=0 };

    pthread_create(&timer_tid, NULL, timer_thread, NULL);
    pthread_create(&sched_tid, NULL, scheduler_thread, NULL);

    pthread_join(sched_tid, NULL);

    /* Timer runs forever; in real code you'd stop it cleanly */
    pthread_cancel(timer_tid);

    return 0;
}
