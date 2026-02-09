#include <atomic>
#include <cstdint>
#include <cstring>
#include <vector>

class SPSCRingBuffer {
public:
    explicit SPSCRingBuffer(size_t capacity)
        : buffer_(capacity),
          capacity_(capacity),
          head_(0),
          tail_(0) {}

    // Disable copy
    SPSCRingBuffer(const SPSCRingBuffer&) = delete;
    SPSCRingBuffer& operator=(const SPSCRingBuffer&) = delete;

    // Push variable-length data
    // Returns false if not enough space
    bool push(const void* data, uint32_t len) {
        const uint32_t total = sizeof(uint32_t) + len;

        size_t head = head_.load(std::memory_order_relaxed);
        size_t tail = tail_.load(std::memory_order_acquire);

        size_t free_space = freeSpace(head, tail);

        if (free_space < total)
            return false;

        size_t space_to_end = capacity_ - head;

        if (space_to_end >= total) {
            // Write normally
            writeRecord(head, data, len);
            advanceHead(head + total);
        } else {
            // Need wrap — check if enough space at beginning
            if (tail <= total)
                return false; // not enough after wrap

            // Write padding marker (length = 0)
            uint32_t zero = 0;
            std::memcpy(&buffer_[head], &zero, sizeof(uint32_t));

            advanceHead(0);  // wrap
            head = 0;

            writeRecord(head, data, len);
            advanceHead(head + total);
        }

        return true;
    }

    // Pop variable-length data
    // Copies into user buffer (must be large enough)
    // Returns false if empty
    bool pop(std::vector<uint8_t>& out) {
        size_t tail = tail_.load(std::memory_order_relaxed);
        size_t head = head_.load(std::memory_order_acquire);

        if (tail == head)
            return false; // empty

        uint32_t len;
        std::memcpy(&len, &buffer_[tail], sizeof(uint32_t));

        if (len == 0) {
            // padding marker → wrap
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

int main () {
    SPSCRingBuffer rb(64 * 1024);

    std::string msg = "hello world";
    rb.push(msg.data(), msg.size());

    std::vector<uint8_t> out;
    if (rb.pop(out)) {
        std::string s(out.begin(), out.end());
    }
}
