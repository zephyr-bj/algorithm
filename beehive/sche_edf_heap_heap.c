#include <stdio.h>
#include <stdlib.h>

#define MAX_TASKS 64
#define MAX_JOBS 128

//---------------------------------------------
// Generic heap
//---------------------------------------------
typedef int (*cmp_fn)(const void*, const void*);

typedef struct {
    void* data[MAX_JOBS];
    int size;
    cmp_fn cmp;
} heap_t;

void swap(void** a, void** b) {
    void* tmp = *a;
    *a = *b;
    *b = tmp;
}

void heapify_up(heap_t* h, int i) {
    while (i > 0) {
        int p = (i - 1) / 2;
        if (h->cmp(h->data[p], h->data[i]) <= 0)
            break;
        swap(&h->data[p], &h->data[i]);
        i = p;
    }
}

void heapify_down(heap_t* h, int i) {
    while (1) {
        int l = 2*i + 1, r = 2*i + 2, s = i;

        if (l < h->size && h->cmp(h->data[l], h->data[s]) < 0)
            s = l;

        if (r < h->size && h->cmp(h->data[r], h->data[s]) < 0)
            s = r;

        if (s == i) break;

        swap(&h->data[i], &h->data[s]);
        i = s;
    }
}

void heap_init(heap_t* h, cmp_fn cmp) {
    h->size = 0;
    h->cmp = cmp;
}

void heap_push(heap_t* h, void* item) {
    h->data[h->size] = item;
    heapify_up(h, h->size);
    h->size++;
}

void* heap_pop(heap_t* h) {
    void* top = h->data[0];
    h->size--;
    h->data[0] = h->data[h->size];
    heapify_down(h, 0);
    return top;
}

void* heap_peek(heap_t* h) {
    return h->size ? h->data[0] : NULL;
}

//---------------------------------------------
// Task / Job definitions
//---------------------------------------------
typedef struct {
    int id;
    int period;
    int execution_time;
    int next_release_time;
} task_t;

typedef struct {
    int id;
    int remaining_time;
    int absolute_deadline;
} job_t;

//---------------------------------------------
// Comparators
//---------------------------------------------
int cmp_release(const void* a, const void* b) {
    const task_t* t1 = (const task_t*)a;
    const task_t* t2 = (const task_t*)b;
    return t1->next_release_time - t2->next_release_time;
}

int cmp_edf(const void* a, const void* b) {
    const job_t* j1 = (const job_t*)a;
    const job_t* j2 = (const job_t*)b;
    return j1->absolute_deadline - j2->absolute_deadline;
}

//---------------------------------------------
// Global storage (avoid malloc)
//---------------------------------------------
task_t tasks[MAX_TASKS];
job_t jobs[MAX_JOBS];

int task_count = 0;
int job_pool_index = 0;

//---------------------------------------------
// Add task
//---------------------------------------------
void add_task(heap_t* release_heap, int id, int period, int exec) {
    tasks[task_count] = (task_t){
        .id = id,
        .period = period,
        .execution_time = exec,
        .next_release_time = 0
    };

    heap_push(release_heap, &tasks[task_count]);
    task_count++;
}

//---------------------------------------------
// Allocate job (simple pool)
//---------------------------------------------
job_t* alloc_job() {
    return &jobs[job_pool_index++];
}

//---------------------------------------------
// Simulation
//---------------------------------------------
void run(int duration) {
    heap_t release_heap;
    heap_t edf_heap;

    heap_init(&release_heap, cmp_release);
    heap_init(&edf_heap, cmp_edf);

    add_task(&release_heap, 1, 5, 2);
    add_task(&release_heap, 2, 7, 3);
    add_task(&release_heap, 3, 10, 1);

    job_t* current = NULL;

    for (int t = 0; t < duration; t++) {

        //-------------------------------------
        // Release phase
        //-------------------------------------
        while (release_heap.size > 0) {
            task_t* task = (task_t*)heap_peek(&release_heap);

            if (task->next_release_time > t)
                break;

            heap_pop(&release_heap);

            job_t* job = alloc_job();
            job->id = task->id;
            job->remaining_time = task->execution_time;
            job->absolute_deadline = t + task->period;

            heap_push(&edf_heap, job);

            task->next_release_time += task->period;
            heap_push(&release_heap, task);
        }

        //-------------------------------------
        // Preemption
        //-------------------------------------
        if (current) {
            job_t* top = (job_t*)heap_peek(&edf_heap);
            if (top && top->absolute_deadline < current->absolute_deadline) {
                heap_push(&edf_heap, current);
                current = (job_t*)heap_pop(&edf_heap);
            }
        }

        //-------------------------------------
        // Pick next
        //-------------------------------------
        if (!current && edf_heap.size > 0) {
            current = (job_t*)heap_pop(&edf_heap);
        }

        //-------------------------------------
        // Execute
        //-------------------------------------
        if (!current) {
            printf("[time %d] IDLE\n", t);
            continue;
        }

        printf("[time %d] Run T%d (dl=%d, rem=%d)\n",
               t, current->id,
               current->absolute_deadline,
               current->remaining_time);

        current->remaining_time--;

        if (t > current->absolute_deadline) {
            printf("  !!! Deadline MISS T%d\n", current->id);
        }

        if (current->remaining_time == 0) {
            current = NULL;
        }
    }
}

//---------------------------------------------
int main() {
    run(50);
    return 0;
}
