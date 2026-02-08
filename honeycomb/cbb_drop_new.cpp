#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define BUFFER_SIZE 128

class rb {
private:
    uint32_t head;
    uint32_t tail;
    std::unique_ptr<char[]> buffer_ptr;
    size_t buf_size;
    size_t rb_space();
    bool rb_empty();
public:
    rbb(size_t sz) : buf_size(sz), buffer_ptr(std::make_unique<char[]>(size)) {}
    ~rbb() {}
    int rb_try_write(const uint8_t *data, uint32_t length);
    bool rb_read(uint8_t *out_data, uint32_t *out_length, uint32_t max_buf_size);
};

size_t rb::rb_space() {
    if (head>tail) {
        return buf_size - (head-tail) - 1;
    } else {
        return tail-head;
    }
}

bool rb::rb_empty() {
    return head==tail;
}

int rb::rb_try_write(const uint8_t *data, uint32_t length) {
    uint32_t required_space = length + sizeof(uint32_t);
    uint32_t space = rb_space();
    if (required_space > space) return space-required_space;

    for (int i = 0; i < sizeof(uint32_t); i++) {
        buffer[head] = ((uint8_t*)&length)[i];
        head = (head + 1) % buf_size;
    }
    for (uint32_t i = 0; i < length; i++) {
        buffer[head] = data[i];
        head = (head + 1) % buf_size;
    }
    return length;
}

// Read data from the buffer
bool rb::rb_read(uint8_t *out_data, uint32_t *out_length, uint32_t max_buf_size) {
    if (is_empty()) return false;

    uint32_t record_len = 0;
    uint32_t temp = tail;
    for (int i = 0; i < sizeof(uint32_t); i++) {
        ((uint8_t*)&record_len)[i] = buffer[temp];
        temp = (temp + 1) % buf_size;
    }

    if (record_len > max_buf_size) return false; // Provided buffer too small
    tail = temp;

    for (uint32_t i = 0; i < record_len; i++) {
        out_data[i] = buffer[tail];
        tail = (tail + 1) % BUFFER_SIZE;
    }

    *out_length = record_len;
    return true;
}
