#include <stdatomic.h>
#include <stdint.h>
#include <string.h>

#define RING_SIZE 1024
#define MSG_SIZE  128

struct log_entry {
    atomic_uint64_t seq;
    uint16_t len;
    char msg[MSG_SIZE];
};

struct ring_buffer {
    atomic_uint64_t head;   // next sequence to write
    struct log_entry buf[RING_SIZE];
};

// initialization
void rb_init(struct ring_buffer *rb)
{
    atomic_init(&rb->head, 0);

    for (int i = 0; i < RING_SIZE; i++) {
        atomic_init(&rb->buf[i].seq, UINT64_MAX);
    }
}

// lockless writer
void rb_write(struct ring_buffer *rb, const char *msg)
{
    /* fetch_add guarantees unique slot ownership */
    uint64_t seq = atomic_fetch_add_explicit(
        &rb->head, 1, memory_order_relaxed);

    struct log_entry *e = &rb->buf[seq % RING_SIZE];

    /* Copy data first */
    size_t len = strnlen(msg, MSG_SIZE - 1);
    memcpy(e->msg, msg, len);
    e->msg[len] = '\0';
    e->len = len;

    /* Publish entry LAST, release ensures data visible before seq update */
    atomic_store_explicit(&e->seq, seq, memory_order_release);
}

// Lockless reader
int rb_read(struct ring_buffer *rb, uint64_t *seq, char *out)
{
    struct log_entry *e = &rb->buf[*seq % RING_SIZE];

    uint64_t seen = atomic_load_explicit(
        &e->seq, memory_order_acquire);

    if (seen != *seq)
        return -1;  // overwritten or not written yet

    memcpy(out, e->msg, e->len + 1);
    (*seq)++;
    return 0;
}

// use example
struct ring_buffer rb;
rb_init(&rb);

/* Writers (multiple CPUs) */
rb_write(&rb, "CPU0: hello");
rb_write(&rb, "CPU1: error");

/* Reader */
uint64_t rseq = atomic_load(&rb.head) - 2;
char buf[MSG_SIZE];

while (rb_read(&rb, &rseq, buf) == 0) {
    // print buf
}
