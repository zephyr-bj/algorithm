#include <atomic>
#include <vector>
#include <cassert>
#include <string>
#include <cstring> // for memcpy

#include <thread>
#include <chrono>
#include <functional>

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
        const uint32_t total = align4(sizeof(Header) + len);
        if (total >= capacity_)
            return false;

        uint64_t reserved;

        // === Phase 1: Reserve space ===
        uint64_t head, tail;
        size_t index, space_to_end;
        size_t padding = 0;
        while (true) {
            head = head_reserve_.load(std::memory_order_relaxed);
            tail = tail_.load(std::memory_order_acquire);

            if (head - tail + total > capacity_)
                return false; // no space (no overwrite)

            index = head & mask_;
            space_to_end = capacity_ - index;
            if (space_to_end < total) {
                padding = space_to_end;
                if (head - tail + total + space_to_end > capacity_)
                    return false;
            }

            if (head_reserve_.compare_exchange_weak(
                    head, head + total + padding,
                    std::memory_order_acquire,
                    std::memory_order_relaxed))
            {
                reserved = head;
                break;
            }
        }

        if (padding > 0) {
            // insert padding
            Header* hdr = reinterpret_cast<Header*>(&buffer_[index]);
            hdr->len = 0;
            hdr->committed = 1;
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
        size_t total = align4(sizeof(Header) + len);

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
    
    static size_t align4(size_t n)
    {
        return (n + 3) & ~size_t(3);
    }

private:
    const size_t capacity_;
    const size_t mask_;

    std::vector<uint8_t> buffer_;

    alignas(64) std::atomic<uint64_t> head_reserve_{0};
    alignas(64) std::atomic<uint64_t> tail_{0};
};

void writeFunc (MPSCRingBuffer &rb, char content, int index, int msg_sz, int interval) {
    for(int i = 0; i < 10; i++) {
        char c = content+i;
        std::string msg = std::string(msg_sz, c);
        bool good = rb.push(msg.data(), msg.size());
        auto now = std::chrono::system_clock::now();
        auto ts = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());
        printf("[%ld] prod[%d]: push return  %d\n", ts.count(), index, good);
        std::this_thread::sleep_for(std::chrono::seconds(interval));
    }
}

int main () {
    MPSCRingBuffer rb(64);

    std::thread producer1 (writeFunc, std::ref(rb), 'a', 0, 11, 1);
    std::thread producer2 (writeFunc, std::ref(rb), '1', 1, 9, 1);

    std::thread consumer ( [&] () {
        for(int i = 0; i < 10; i++) {
            std::vector<uint8_t> out;
            if (rb.pop(out)) {
                std::string s(out.begin(), out.end());
                printf("out data %s\n", s.c_str());
            } else {
                printf("pop failed\n");
            }
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    });

    producer1.join();
    producer2.join();
    consumer.join();
}

