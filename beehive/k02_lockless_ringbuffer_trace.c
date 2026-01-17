#include <stdatomic.h>
#include <stdint.h>
#include <string.h>

#define TRACE_BUF_SIZE 4096
#define TRACE_MAX_CPUS 64
#define TRACE_MSG_SIZE 64

struct trace_event {
    uint32_t len;
    uint32_t type;
    uint64_t ts;
    char data[TRACE_MSG_SIZE];
};

struct trace_ring {
    atomic_uint write_pos;
    atomic_uint read_pos;
    char buffer[TRACE_BUF_SIZE];
};

struct trace_system {
    struct trace_ring cpu_rb[TRACE_MAX_CPUS];
};

// Initialization
void trace_rb_init(struct trace_ring *rb)
{
    atomic_init(&rb->write_pos, 0);
    atomic_init(&rb->read_pos, 0);
}

// Timestamp helper
static inline uint64_t trace_clock(void)
{
    return __builtin_readcyclecounter();  // placeholder
}

// Lockless writter
void trace_write(struct trace_ring *rb,
                 uint32_t type,
                 const void *data,
                 uint32_t len)
{
    struct trace_event ev;
    uint32_t total_len;

    if (len > TRACE_MSG_SIZE)
        len = TRACE_MSG_SIZE;

    ev.type = type;
    ev.len  = len;
    ev.ts   = trace_clock();
    memcpy(ev.data, data, len);

    total_len = sizeof(ev.type) +
                sizeof(ev.len) +
                sizeof(ev.ts) +
                len;

    uint32_t w = atomic_load_explicit(
        &rb->write_pos, memory_order_relaxed);

    /* Wrap if needed */
    if (w + total_len > TRACE_BUF_SIZE) {
        w = 0;
        atomic_store_explicit(
            &rb->write_pos, 0, memory_order_relaxed);
    }

    memcpy(&rb->buffer[w], &ev, total_len);

    atomic_store_explicit(
        &rb->write_pos, w + total_len, memory_order_release);
}

// Reader
int trace_read(struct trace_ring *rb, void *out, uint32_t *len)
{
    uint32_t r = atomic_load_explicit(
        &rb->read_pos, memory_order_relaxed);

    uint32_t w = atomic_load_explicit(
        &rb->write_pos, memory_order_acquire);

    if (r == w)
        return -1;  // empty

    struct trace_event *ev =
        (struct trace_event *)&rb->buffer[r];

    uint32_t total_len =
        sizeof(ev->type) +
        sizeof(ev->len) +
        sizeof(ev->ts) +
        ev->len;

    memcpy(out, ev, total_len);

    r += total_len;
    if (r >= TRACE_BUF_SIZE)
        r = 0;

    atomic_store_explicit(
        &rb->read_pos, r, memory_order_release);

    *len = total_len;
    return 0;
}

// Multi-CPU Read Aggregation
for (cpu = 0; cpu < nr_cpus; cpu++)
    trace_read(&sys->cpu_rb[cpu], ...);

