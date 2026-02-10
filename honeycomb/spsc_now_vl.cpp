#include <atomic>
#include <vector>
#include <cassert>
#include <string>

class SPSCRingBuffer {
public:
    explicit SPSCRingBuffer(size_t size)
        : capacity_(round_up_pow2(size)),
          mask_(capacity_ - 1),
          buffer_(capacity_),
          head_(0),
          tail_(0)
    {
        assert((capacity_ & (capacity_ - 1)) == 0);
        assert(capacity_ >= 16);
    }

    bool push(const void* data, uint32_t len)
    {
        size_t header_size = sizeof(uint32_t);
        size_t total = align4(header_size + len);

        size_t head = head_.load(std::memory_order_relaxed);
        size_t tail = tail_.load(std::memory_order_acquire);

        if ((head - tail) + total > capacity_)
            return false; // no overwrite

        size_t write_pos = head & mask_;
        size_t space_to_end = capacity_ - write_pos;

        // ---- wrap handling
        if (space_to_end < total) {
            if (space_to_end >= header_size) {
                uint32_t marker = UINT32_MAX;
                std::memcpy(&buffer_[write_pos], &marker, sizeof(marker));
            }
            head += space_to_end;
            write_pos = 0;
        }
        if ((head - tail) + total > capacity_)
            return false; // no overwrite

        std::memcpy(&buffer_[write_pos], &len, header_size);
        std::memcpy(&buffer_[write_pos + header_size], data, len);
        head_.store(head + total, std::memory_order_release);
        return true;
    }

    bool pop(std::vector<uint8_t>& out)
    {
        size_t header_size = sizeof(uint32_t);

        size_t tail = tail_.load(std::memory_order_relaxed);
        size_t head = head_.load(std::memory_order_acquire);

        if (tail == head)
            return false;

        size_t read_pos = tail & mask_;
        uint32_t len;

        std::memcpy(&len, &buffer_[read_pos], header_size);

        // ---- padding marker?
        if (len == UINT32_MAX)
        {
            size_t space_to_end = capacity_ - read_pos;
            tail += space_to_end;
            read_pos = 0;

            std::memcpy(&len, &buffer_[read_pos], header_size);
        }

        size_t total = align4(header_size + len);
        
        out.resize(len);
        if (tail + total > head)
            return false; // incomplete record

        std::memcpy(out.data(),
                    &buffer_[read_pos + header_size],
                    len);
        tail_.store(tail + total, std::memory_order_release);
        return true;
    }

    size_t size() const
    {
        return head_.load(std::memory_order_acquire) -
               tail_.load(std::memory_order_acquire);
    }

private:
    static size_t align4(size_t n)
    {
        return (n + 3) & ~size_t(3);
    }

    static size_t round_up_pow2(size_t v)
    {
        size_t p = 1;
        while (p < v) p <<= 1;
        return p;
    }

private:
    const size_t capacity_;
    const size_t mask_;
    std::vector<uint8_t> buffer_;

    alignas(64) std::atomic<size_t> head_;
    alignas(64) std::atomic<size_t> tail_;
};

int main () {
    SPSCRingBuffer rb(64 * 1024);

    std::string msg = "hello world";
    rb.push(msg.data(), msg.size());

    std::vector<uint8_t> out;
    if (rb.pop(out)) {
        std::string s(out.begin(), out.end());
        printf("out data %s\n", s.c_str());
    }
}

/*
Memory Ordering
Producer:
Loads tail with acquire → sees consumer progress
Stores head with release → publishes data

Consumer:
Loads head with acquire → sees producer data
Stores tail with release → publishes consumption
*/
