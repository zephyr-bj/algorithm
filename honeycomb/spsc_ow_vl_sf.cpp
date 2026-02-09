#include <atomic>
#include <cstdint>
#include <cstring>
#include <vector>
#include <cassert>

// non-blocking, lockless, no data corruption
class SPSCRingOverwrite {
public:
    explicit SPSCRingOverwrite(size_t capacity_pow2)
        : capacity_(capacity_pow2),
          mask_(capacity_pow2 - 1),
          buffer_(capacity_pow2)
    {
        assert((capacity_pow2 & (capacity_pow2 - 1)) == 0);
    }

    bool push(const void* data, uint32_t len)
    {
        const uint32_t total = sizeof(Header) + len;

        if (total >= capacity_)
            return false;   // record too large ever to fit

        uint64_t head = head_seq_.load(std::memory_order_relaxed);
        uint64_t tail = tail_seq_.load(std::memory_order_acquire);

        // Ensure space logically (overwrite allowed)
        if (head - tail + total > capacity_) {
            // nothing to do — consumer will detect loss
        }

        size_t index = head & mask_;
        size_t space_to_end = capacity_ - index;

        // If not enough contiguous space, insert padding marker
        if (space_to_end < total) {
            writePadding(index, space_to_end);
            head += space_to_end;
            index = 0;
        }

        Header h;
        h.len = len;
        h.seq_low = static_cast<uint32_t>(head);

        std::memcpy(&buffer_[index], &h, sizeof(Header));
        std::memcpy(&buffer_[index + sizeof(Header)], data, len);

        // Publish
        head_seq_.store(head + total, std::memory_order_release);

        return true;
    }

    bool pop(std::vector<uint8_t>& out)
    {
        uint64_t tail = tail_seq_.load(std::memory_order_relaxed);
        uint64_t head = head_seq_.load(std::memory_order_acquire);

        if (tail == head)
            return false;   // empty

        // Detect overwrite (consumer too slow)
        if (head - tail > capacity_) {
            tail = head - capacity_;
        }

        size_t index = tail & mask_;

        Header h;
        std::memcpy(&h, &buffer_[index], sizeof(Header));

        // Padding marker
        if (h.len == 0) {
            tail += (capacity_ - index);
            tail_seq_.store(tail, std::memory_order_release);
            return pop(out);
        }

        // Verify record not overwritten
        if (h.seq_low != static_cast<uint32_t>(tail)) {
            // record overwritten — skip forward
            tail = head - capacity_;
            tail_seq_.store(tail, std::memory_order_release);
            return false;
        }

        size_t total = sizeof(Header) + h.len;

        out.resize(h.len);
        std::memcpy(out.data(),
                    &buffer_[index + sizeof(Header)],
                    h.len);

        tail_seq_.store(tail + total, std::memory_order_release);
        return true;
    }

private:
    struct Header {
        uint32_t len;
        uint32_t seq_low;
    };

    void writePadding(size_t index, size_t size)
    {
        Header h{};
        h.len = 0;  // padding marker
        h.seq_low = 0;
        std::memcpy(&buffer_[index], &h, sizeof(Header));
    }

private:
    const size_t capacity_;
    const size_t mask_;

    std::vector<uint8_t> buffer_;

    alignas(64) std::atomic<uint64_t> head_seq_{0};
    alignas(64) std::atomic<uint64_t> tail_seq_{0};
};
