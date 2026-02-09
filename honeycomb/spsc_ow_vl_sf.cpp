#include <atomic>
#include <cstdint>
#include <cstring>
#include <vector>
#include <cassert>

// non-blocking, lockless, no data corruption
#include <atomic>
#include <cstdint>
#include <cstring>
#include <vector>
#include <cassert>

class SPSCRingBuffer {
public:
    explicit SPSCRingBuffer(size_t size)
        : capacity_(round_up_pow2(size)),
          mask_(capacity_ - 1),
          buffer_(capacity_),
          head_(0),
          tail_(0),
          next_seq_(1)
    {
        assert((capacity_ & (capacity_ - 1)) == 0);
        assert(capacity_ >= 32);
    }

    // ------------------------------------------------------------
    // Producer
    // ------------------------------------------------------------
    bool push(const void* data, uint32_t len)
    {
        if (len == 0 || len == UINT32_MAX)
            return false;

        constexpr size_t header_size = 8;
        size_t total = align4(header_size + len);

        size_t head = head_.load(std::memory_order_relaxed);
        size_t tail = tail_.load(std::memory_order_acquire);

        // ---- overwrite oldest until space exists
        while ((head - tail) + total > capacity_)
        {
            if (!discard_one(tail))
                break;
        }

        size_t write_pos = head & mask_;
        size_t space_to_end = capacity_ - write_pos;

        // ---- wrap handling
        if (space_to_end < total)
        {
            if (space_to_end >= sizeof(uint32_t))
                write_padding(write_pos);

            head += space_to_end;
            write_pos = 0;
        }

        uint32_t seq = next_seq_++;

        // ---- write header
        std::memcpy(&buffer_[write_pos + 0], &seq, sizeof(uint32_t));
        std::memcpy(&buffer_[write_pos + 4], &len, sizeof(uint32_t));

        // ---- write payload
        std::memcpy(&buffer_[write_pos + header_size], data, len);

        // ---- optional: zero padding (debug)
        size_t used = header_size + len;
        size_t pad = total - used;
        if (pad)
            std::memset(&buffer_[write_pos + used], 0, pad);

        head_.store(head + total, std::memory_order_release);
        return true;
    }

    // ------------------------------------------------------------
    // Consumer
    // ------------------------------------------------------------
    bool pop(std::vector<uint8_t>& out, uint32_t& seq_out)
    {
        constexpr size_t header_size = 8;

        size_t tail = tail_.load(std::memory_order_relaxed);
        size_t head = head_.load(std::memory_order_acquire);

        if (tail == head)
            return false;

        size_t read_pos = tail & mask_;

        uint32_t len;
        std::memcpy(&len, &buffer_[read_pos + 4], sizeof(uint32_t));

        // ---- padding marker
        if (len == UINT32_MAX)
        {
            size_t space_to_end = capacity_ - read_pos;
            tail += space_to_end;
            read_pos = 0;

            std::memcpy(&len, &buffer_[read_pos + 4], sizeof(uint32_t));
        }

        if (len == 0 || len == UINT32_MAX)
            return false;

        size_t total = align4(header_size + len);
        if (tail + total > head)
            return false; // incomplete write

        uint32_t seq;
        std::memcpy(&seq, &buffer_[read_pos + 0], sizeof(uint32_t));

        out.resize(len);
        std::memcpy(out.data(),
                    &buffer_[read_pos + header_size],
                    len);

        seq_out = seq;
        tail_.store(tail + total, std::memory_order_release);
        return true;
    }

private:
    // ------------------------------------------------------------
    // Drop exactly one oldest record
    // ------------------------------------------------------------
    bool discard_one(size_t& tail)
    {
        constexpr size_t header_size = 8;

        size_t head = head_.load(std::memory_order_acquire);
        if (tail == head)
            return false;

        size_t pos = tail & mask_;
        uint32_t len;

        std::memcpy(&len, &buffer_[pos + 4], sizeof(uint32_t));

        if (len == UINT32_MAX)
        {
            size_t space_to_end = capacity_ - pos;
            tail += space_to_end;
            tail_.store(tail, std::memory_order_release);
            return true;
        }

        if (len == 0 || len == UINT32_MAX)
            return false;

        size_t total = align4(header_size + len);
        tail += total;
        tail_.store(tail, std::memory_order_release);
        return true;
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
        std::memcpy(&buffer_[pos + 4], &marker, sizeof(marker));
    }

private:
    const size_t capacity_;
    const size_t mask_;
    std::vector<uint8_t> buffer_;

    alignas(64) std::atomic<size_t> head_;
    alignas(64) std::atomic<size_t> tail_;

    uint32_t next_seq_; // producer-only
};

