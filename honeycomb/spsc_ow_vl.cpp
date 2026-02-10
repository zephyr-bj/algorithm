// non-blocking, lockless, no data corruption
#include <atomic>
#include <vector>
#include <cassert>
#include <string>

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
        const uint32_t total = align4(sizeof(Header) + len);

        if (total >= capacity_)
            return false;   // record too large ever to fit

        uint64_t head = head_.load(std::memory_order_relaxed);
        //uint64_t tail = tail_.load(std::memory_order_acquire);

        size_t write_pos = head & mask_;
        size_t space_to_end = capacity_ - write_pos;

        // If not enough contiguous space, insert padding marker
        if (space_to_end < total) {
            Header h{};
            h.len = UINT32_MAX;  // padding marker
            h.seq_low = 0;
            std::memcpy(&buffer_[write_pos], &h, sizeof(Header));
            head += space_to_end;
            write_pos = 0;
        }

        Header h;
        h.len = len;
        h.seq_low = static_cast<uint32_t>(head);

        std::memcpy(&buffer_[write_pos], &h, sizeof(Header));
        std::memcpy(&buffer_[write_pos + sizeof(Header)], data, len);

        // Publish
        head_.store(head + total, std::memory_order_release);

        return true;
    }

    bool pop(std::vector<uint8_t>& out)
    {
        uint64_t tail = tail_.load(std::memory_order_relaxed);
        uint64_t head = head_.load(std::memory_order_acquire);

        if (tail == head)
            return false;   // empty

        // Detect overwrite (consumer too slow)
        if (head - tail > capacity_) {
            tail = head - capacity_;
        }

        size_t read_pos = tail & mask_;

        Header h;
        std::memcpy(&h, &buffer_[read_pos], sizeof(Header));

        // Padding marker
        if (h.len == UINT32_MAX) {
            tail += (capacity_ - read_pos);
            tail_.store(tail, std::memory_order_release);
            return pop(out);
        }

        // Verify record not overwritten
        if (h.seq_low != static_cast<uint32_t>(tail)) {
            // record overwritten — skip forward
            tail = head - capacity_;
            tail_.store(tail, std::memory_order_release);
            return false;
        }

        size_t total = align4(sizeof(Header) + h.len);

        out.resize(h.len);
        std::memcpy(out.data(),
                    &buffer_[read_pos + sizeof(Header)],
                    h.len);

        tail_.store(tail + total, std::memory_order_release);
        return true;
    }

private:
    struct Header {
        uint32_t len;
        uint32_t seq_low;
    };

private:
    static size_t align4(size_t n)
    {
        return (n + 3) & ~size_t(3);
    }
    const size_t capacity_;
    const size_t mask_;

    std::vector<uint8_t> buffer_;

    alignas(64) std::atomic<uint64_t> head_{0};
    alignas(64) std::atomic<uint64_t> tail_{0};
};


int main () {
    SPSCRingOverwrite rb(64 * 1024);

    std::string msg = "hello world";
    rb.push(msg.data(), msg.size());

    std::vector<uint8_t> out;
    if (rb.pop(out)) {
        std::string s(out.begin(), out.end());
        printf("out data %s\n", s.c_str());
    }
}
