/*
[Producer threads]
        ↓   (lock-free MPSC queue)
   release_queue  (task events)
        ↓
[Scheduler thread]
   EDF min-heap (owned)
        ↓
     execution
*/
/*
✔ Lock-free where it matters
Producers → MPSC queue (lock-free)
✔ No locks in scheduler
Scheduler is single-threaded
Owns both heaps → no contention
*/

/*
need malloc, use a memory poll
*/

/*
For a periodic task:

Period = T
Release time = r_k
Deadline (implicit model): d_k = r_k + T 

k
	​

+T*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>
#include <unistd.h>

#define MAX_JOBS 1024
#define QSIZE 1024

//---------------------------------------------
// Lock-free MPSC queue
//---------------------------------------------
typedef struct {
    void* buf[QSIZE];
    atomic_uint head;
    atomic_uint tail;
} mpsc_queue_t;

void q_init(mpsc_queue_t* q) {
    atomic_init(&q->head, 0);
    atomic_init(&q->tail, 0);
}

int enqueue(mpsc_queue_t* q, void* item) {
    unsigned head = atomic_load_explicit(&q->head, memory_order_relaxed);

    while (1) {
        unsigned tail = atomic_load_explicit(&q->tail, memory_order_acquire);

        if ((head - tail) >= QSIZE)
            return 0; // full

        if (atomic_compare_exchange_weak_explicit(
                &q->head, &head, head + 1,
                memory_order_acq_rel, memory_order_relaxed)) {

            q->buf[head % QSIZE] = item;
            return 1;
        }
    }
}

void* dequeue(mpsc_queue_t* q) {
    unsigned tail = atomic_load_explicit(&q->tail, memory_order_relaxed);
    unsigned head = atomic_load_explicit(&q->head, memory_order_acquire);

    if (tail == head)
        return NULL;

    void* item = q->buf[tail % QSIZE];
    atomic_store_explicit(&q->tail, tail + 1, memory_order_release);
    return item;
}

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
    void* t = *a; *a = *b; *b = t;
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
        int l = 2*i+1, r = 2*i+2, s = i;

        if (l < h->size && h->cmp(h->data[l], h->data[s]) < 0) s = l;
        if (r < h->size && h->cmp(h->data[r], h->data[s]) < 0) s = r;

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
// Task / Job
//---------------------------------------------
typedef struct {
    int id;
    int period;
    int execution_time;
    int next_release;
} task_t;

typedef struct {
    int id;
    int remaining;
    int deadline;
} job_t;

//---------------------------------------------
// Comparators
//---------------------------------------------
int cmp_edf(const void* a, const void* b) {
    const job_t* j1 = a;
    const job_t* j2 = b;
    if (j1->deadline < j2->deadline) return -1;
    if (j1->deadline > j2->deadline) return 1;
    return 0;
}

//---------------------------------------------
// Globals
//---------------------------------------------
mpsc_queue_t release_q;
heap_t edf_heap;

atomic_int running = 1;

//---------------------------------------------
// Producer thread (periodic release)
//---------------------------------------------
void* producer(void* arg) {
    task_t* t = (task_t*)arg;
    int time = 0;

    while (atomic_load(&running)) {

        if (time >= t->next_release) {
            enqueue(&release_q, t);
            t->next_release += t->period;
        }

        usleep(1000); // simulate time passing
        time++;
    }
    return NULL;
}

//---------------------------------------------
// Scheduler thread
//---------------------------------------------
void* scheduler(void* arg) {
    int time = 0;
    job_t* current = NULL;

    while (time < 50) {

        //---------------------------------
        // Drain release queue
        //---------------------------------
        void* msg;
        while ((msg = dequeue(&release_q)) != NULL) {

            task_t* t = msg;

            job_t* j = malloc(sizeof(job_t));
            j->id = t->id;
            j->remaining = t->execution_time;
            j->deadline = time + t->period;

            heap_push(&edf_heap, j);
        }

        //---------------------------------
        // Preemption
        //---------------------------------
        if (current) {
            job_t* top = heap_peek(&edf_heap);
            if (top && top->deadline < current->deadline) {
                heap_push(&edf_heap, current);
                current = heap_pop(&edf_heap);
            }
        }

        //---------------------------------
        // Pick next
        //---------------------------------
        if (!current && edf_heap.size > 0) {
            current = heap_pop(&edf_heap);
        }

        //---------------------------------
        // Execute
        //---------------------------------
        if (!current) {
            printf("[time %d] IDLE\n", time);
        } else {
            printf("[time %d] Run T%d (dl=%d, rem=%d)\n",
                   time, current->id,
                   current->deadline,
                   current->remaining);

            current->remaining--;

            if (current->remaining == 0) {
                free(current);
                current = NULL;
            }
        }

        usleep(1000);
        time++;
    }

    atomic_store(&running, 0);
    return NULL;
}

//---------------------------------------------
// Main
//---------------------------------------------
int main() {
    q_init(&release_q);
    heap_init(&edf_heap, cmp_edf);

    task_t t1 = {1, 5, 2, 0};
    task_t t2 = {2, 7, 3, 0};
    task_t t3 = {3, 10, 1, 0};

    pthread_t p1, p2, p3, sched;

    pthread_create(&p1, NULL, producer, &t1);
    pthread_create(&p2, NULL, producer, &t2);
    pthread_create(&p3, NULL, producer, &t3);

    pthread_create(&sched, NULL, scheduler, NULL);

    pthread_join(sched, NULL);

    return 0;
}
