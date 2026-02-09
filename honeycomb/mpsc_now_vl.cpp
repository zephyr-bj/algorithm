#include <atomic>
#include <cstdint>
#include <cstring>
#include <vector>
#include <cassert>
#include <string>

class MPSCRingBuffer {
public:
    explicit MPSCRingBuffer(size_t capacity_pow2)
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
            return false;

        uint64_t reserved;

        // === Phase 1: Reserve space ===
        while (true) {
            uint64_t head = head_reserve_.load(std::memory_order_relaxed);
            uint64_t tail = tail_.load(std::memory_order_acquire);

            if (head - tail + total > capacity_)
                return false; // no space (no overwrite)

            if (head_reserve_.compare_exchange_weak(
                    head, head + total,
                    std::memory_order_acquire,
                    std::memory_order_relaxed))
            {
                reserved = head;
                break;
            }
        }

        size_t index = reserved & mask_;
        size_t space_to_end = capacity_ - index;

        if (space_to_end < total) {
            // insert padding
            writePadding(index, space_to_end);
            reserved += space_to_end;
            index = 0;
        }

        // === Phase 2: Write record ===
        Header* hdr = reinterpret_cast<Header*>(&buffer_[index]);
        hdr->len = len;
        hdr->committed = 0;

        std::memcpy(&buffer_[index + sizeof(Header)], data, len);

        // publish payload before marking committed
        std::atomic_thread_fence(std::memory_order_release);
        hdr->committed = 1;

        return true;
    }

    bool pop(std::vector<uint8_t>& out)
    {
        uint64_t tail = tail_.load(std::memory_order_relaxed);
        uint64_t head = head_reserve_.load(std::memory_order_acquire);

        if (tail == head)
            return false;

        size_t index = tail & mask_;
        Header* hdr = reinterpret_cast<Header*>(&buffer_[index]);

        if (hdr->len == 0) {
            // padding
            tail += (capacity_ - index);
            tail_.store(tail, std::memory_order_release);
            return pop(out);
        }

        if (hdr->committed == 0)
            return false; // producer not finished

        uint32_t len = hdr->len;
        size_t total = sizeof(Header) + len;

        out.resize(len);
        std::memcpy(out.data(),
                    &buffer_[index + sizeof(Header)],
                    len);

        tail_.store(tail + total, std::memory_order_release);
        return true;
    }

private:
    struct Header {
        uint32_t len;
        uint32_t committed;
    };

    void writePadding(size_t index, size_t)
    {
        Header* hdr = reinterpret_cast<Header*>(&buffer_[index]);
        hdr->len = 0;
        hdr->committed = 1;
    }

private:
    const size_t capacity_;
    const size_t mask_;

    std::vector<uint8_t> buffer_;

    alignas(64) std::atomic<uint64_t> head_reserve_{0};
    alignas(64) std::atomic<uint64_t> tail_{0};
};


int main () {
    MPSCRingBuffer rb(64 * 1024);

    std::string msg = "hello world";
    rb.push(msg.data(), msg.size());

    std::vector<uint8_t> out;
    if (rb.pop(out)) {
        std::string s(out.begin(), out.end());
        printf("out data %s\n", s.c_str());
    }
}

