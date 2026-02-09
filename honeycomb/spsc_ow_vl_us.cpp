#include <atomic>
#include <cstdint>
#include <cstring>
#include <vector>
// This is common in embedded logging: 
// occasional loss is acceptable.
// Occasional corruption is acceptable
// prioritize simplicity

// spsc overwrite varying length, unsafe

// non-blocking, lockless
class SPSCRingBufferOverwrite {
public:
    explicit SPSCRingBufferOverwrite(size_t capacity)
        : buffer_(capacity),
          capacity_(capacity),
          head_(0),
          tail_(0) {}

    // Push always succeeds (unless record > capacity)
    bool push(const void* data, uint32_t len) {
        const uint32_t total = sizeof(uint32_t) + len;

        if (total >= capacity_)
            return false; // record too large ever to fit

        size_t head = head_.load(std::memory_order_relaxed);
        size_t tail = tail_.load(std::memory_order_acquire);

        // Ensure enough space by dropping old records
        while (freeSpace(head, tail) < total) {
            tail = dropOne(tail);
        }

        size_t space_to_end = capacity_ - head;

        if (space_to_end >= total) {
            writeRecord(head, data, len);
            advanceHead(head + total);
        } else {
            // Insert padding marker
            uint32_t zero = 0;
            std::memcpy(&buffer_[head], &zero, sizeof(uint32_t));
            advanceHead(0);

            head = 0;

            writeRecord(head, data, len);
            advanceHead(head + total);
        }

        return true;
    }

    bool pop(std::vector<uint8_t>& out) {
        size_t tail = tail_.load(std::memory_order_relaxed);
        size_t head = head_.load(std::memory_order_acquire);

        if (tail == head)
            return false; // empty

        uint32_t len;
        std::memcpy(&len, &buffer_[tail], sizeof(uint32_t));

        if (len == 0) {
            tail = 0;
            tail_.store(tail, std::memory_order_release);
            return pop(out);
        }

        size_t total = sizeof(uint32_t) + len;

        out.resize(len);
        std::memcpy(out.data(), &buffer_[tail + sizeof(uint32_t)], len);

        advanceTail(tail + total);

        return true;
    }

private:
    size_t freeSpace(size_t head, size_t tail) const {
        if (head >= tail)
            return capacity_ - (head - tail);
        else
            return tail - head;
    }

    // Drop one record from tail (used by producer)
    size_t dropOne(size_t tail) {
        uint32_t len;
        std::memcpy(&len, &buffer_[tail], sizeof(uint32_t));

        if (len == 0) {
            tail = 0;
            tail_.store(tail, std::memory_order_release);
            return tail;
        }

        size_t total = sizeof(uint32_t) + len;
        size_t new_tail = (tail + total) % capacity_;

        tail_.store(new_tail, std::memory_order_release);
        return new_tail;
    }

    void writeRecord(size_t pos, const void* data, uint32_t len) {
        std::memcpy(&buffer_[pos], &len, sizeof(uint32_t));
        std::memcpy(&buffer_[pos + sizeof(uint32_t)], data, len);
    }

    void advanceHead(size_t new_head) {
        head_.store(new_head % capacity_, std::memory_order_release);
    }

    void advanceTail(size_t new_tail) {
        tail_.store(new_tail % capacity_, std::memory_order_release);
    }

private:
    std::vector<uint8_t> buffer_;
    const size_t capacity_;

    alignas(64) std::atomic<size_t> head_; // producer owns
    alignas(64) std::atomic<size_t> tail_; // consumer owns
};
