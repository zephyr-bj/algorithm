#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define BUFFER_SIZE 128

typedef struct {
    uint8_t buffer[BUFFER_SIZE];
    uint32_t head; 
    uint32_t tail; 
    uint32_t count; 
} RingBuffer;

// Helper to move the tail forward by one full record to free space
void rb_discard_oldest(RingBuffer *rb) {
    if (rb->count == 0) return;

    // 1. Read the length of the oldest record
    uint32_t record_len = 0;
    for (int i = 0; i < sizeof(uint32_t); i++) {
        ((uint8_t*)&record_len)[i] = rb->buffer[rb->tail];
        rb->tail = (rb->tail + 1) % BUFFER_SIZE;
    }

    // 2. Advance tail past the payload
    rb->tail = (rb->tail + record_len) % BUFFER_SIZE;
    
    // 3. Decrease total count by (Header + Payload)
    rb->count -= (sizeof(uint32_t) + record_len);
}

void rb_write_overwrite(RingBuffer *rb, const uint8_t *data, uint32_t length) {
    uint32_t required_space = length + sizeof(uint32_t);

    // If the record is bigger than the buffer itself, we can't store it
    if (required_space > BUFFER_SIZE) return;

    // While not enough space, delete the oldest records
    while (BUFFER_SIZE - rb->count < required_space) {
        rb_discard_oldest(rb);
    }

    // Now we have enough space, perform the write
    // Write Header
    for (int i = 0; i < sizeof(uint32_t); i++) {
        rb->buffer[rb->head] = ((uint8_t*)&length)[i];
        rb->head = (rb->head + 1) % BUFFER_SIZE;
    }

    // Write Payload
    for (uint32_t i = 0; i < length; i++) {
        rb->buffer[rb->head] = data[i];
        rb->head = (rb->head + 1) % BUFFER_SIZE;
    }

    rb->count += required_space;
}

// Read data from the buffer
bool rb_read(RingBuffer *rb, uint8_t *out_data, uint32_t *out_length, uint32_t max_buf_size) {
    if (rb->count == 0) return false;

    // 1. Read the length header
    uint32_t record_len = 0;
    for (int i = 0; i < sizeof(uint32_t); i++) {
        ((uint8_t*)&record_len)[i] = rb->buffer[rb->tail];
        rb->tail = (rb->tail + 1) % BUFFER_SIZE;
    }

    // 2. Read the payload
    if (record_len > max_buf_size) return false; // Provided buffer too small

    for (uint32_t i = 0; i < record_len; i++) {
        out_data[i] = rb->buffer[rb->tail];
        rb->tail = (rb->tail + 1) % BUFFER_SIZE;
    }

    *out_length = record_len;
    rb->count -= (record_len + sizeof(uint32_t));
    return true;
}
