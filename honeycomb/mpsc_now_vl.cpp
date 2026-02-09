#include <atomic>
#include <cstdint>
#include <cstring>
#include <vector>
#include <cassert>
#include <string>

#include <atomic>
#include <cstdint>
#include <cstring>
#include <vector>
#include <cassert>

class MPSCRingBuffer {
public:
    explicit MPSCRingBuffer(size_t size)
        : capacity_(round_up_pow2(size)),
          mask_(capacity_ - 1),
          buffer_(capacity_),
          head_reserve_(0),
          head_commit_(0),
          tail_(0)
    {
        assert((capacity_ & (capacity_ - 1)) == 0);
        assert(capacity_ >= 64);
    }

    // ------------------------------------------------------------
    // Producer (multi)
    // ------------------------------------------------------------
    bool push(const void* data, uint32_t len)
    {
        if (len == 0 || len == UINT32_MAX)
            return false;

        constexpr size_t header_size = 8;
        size_t total = align4(header_size + len);

        // ---- reserve space
        size_t reserve = head_reserve_.fetch_add(total,
                              std::memory_order_acq_rel);

        size_t tail = tail_.load(std::memory_order_acquire);
        if ((reserve - tail) + total > capacity_)
        {
            // rollback reservation
            head_reserve_.fetch_sub(total, std::memory_order_release);
            return false;
        }

        size_t pos = reserve & mask_;
        size_t space_to_end = capacity_ - pos;

        // ---- wrap padding
        if (space_to_end < total)
        {
            if (space_to_end >= sizeof(uint32_t))
                write_padding(pos);

            reserve += space_to_end;
            pos = 0;
        }

        // ---- write header
        std::memcpy(&buffer_[pos + 0], &len, sizeof(uint32_t));
        uint32_t committed = 0;
        std::memcpy(&buffer_[pos + 4], &committed, sizeof(uint32_t));

        // ---- write payload
        std::memcpy(&buffer_[pos + header_size], data, len);

        // ---- publish commit flag
        committed = 1;
        std::memcpy(&buffer_[pos + 4], &committed, sizeof(uint32_t));

        // ---- advance commit pointer in order
        publish_commit(reserve, total);

        return true;
    }

    // ------------------------------------------------------------
    // Consumer (single)
    // ------------------------------------------------------------
    bool pop(std::vector<uint8_t>& out)
    {
        constexpr size_t header_size = 8;

        size_t tail = tail_.load(std::memory_order_relaxed);
        size_t head = head_commit_.load(std::memory_order_acquire);

        if (tail == head)
            return false;

        size_t pos = tail & mask_;

        uint32_t len;
        std::memcpy(&len, &buffer_[pos + 0], sizeof(uint32_t));

        // ---- padding marker
        if (len == UINT32_MAX)
        {
            size_t space_to_end = capacity_ - pos;
            tail += space_to_end;
            tail_.store(tail, std::memory_order_release);
            return false;
        }

        uint32_t committed;
        std::memcpy(&committed, &buffer_[pos + 4], sizeof(uint32_t));
        if (!committed)
            return false; // not ready yet

        size_t total = align4(header_size + len);

        out.resize(len);
        std::memcpy(out.data(),
                    &buffer_[pos + header_size],
                    len);

        tail_.store(tail + total, std::memory_order_release);
        return true;
    }

private:
    // ------------------------------------------------------------
    // Commit publishing (ordered)
    // ------------------------------------------------------------
    void publish_commit(size_t reserve, size_t total)
    {
        size_t expected = reserve;
        while (!head_commit_.compare_exchange_weak(
                   expected,
                   reserve + total,
                   std::memory_order_release,
                   std::memory_order_relaxed))
        {
            expected = reserve;
        }
    }

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

    void write_padding(size_t pos)
    {
        uint32_t marker = UINT32_MAX;
        std::memcpy(&buffer_[pos + 0], &marker, sizeof(marker));
    }

private:
    const size_t capacity_;
    const size_t mask_;
    std::vector<uint8_t> buffer_;

    alignas(64) std::atomic<size_t> head_reserve_;
    alignas(64) std::atomic<size_t> head_commit_;
    alignas(64) std::atomic<size_t> tail_;
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

