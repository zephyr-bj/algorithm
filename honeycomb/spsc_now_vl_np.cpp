#include <atomic>
#include <vector>
#include <cassert>
#include <string>

#include <cstring> //for memcpy

#include <thread>
#include <chrono>

//single producer single consumer, no overwrite, varying length, no padding

class SPSCRingBuffer {
public:
    explicit SPSCRingBuffer(size_t size)
        : capacity_(size),
          buffer_(capacity_),
          head_(0),
          tail_(0)
    {
    }

    bool push(const void* data, uint32_t len)
    {
        size_t header_size = sizeof(uint32_t);
        size_t head = head_.load(std::memory_order_relaxed);
        size_t tail = tail_.load(std::memory_order_acquire);

        size_t total = len + header_size;
        if ((head - tail) + total > capacity_)
            return false; // no overwrite

        size_t write_pos = head % capacity_;

        uint8_t * pLen = (uint8_t*)(&len);
        for(int i = 0; i < header_size; i++) {
            buffer_[write_pos] = pLen[i];
            write_pos = (write_pos + 1) % capacity_;
        }

        uint8_t * pData = (uint8_t*)data;
        for(int i = 0; i < len; i++) {
            buffer_[write_pos] = pData[i];
            write_pos = (write_pos + 1) % capacity_;
        }
        head_.store(head + total, std::memory_order_release);
        return true;
    }

    bool pop(std::vector<uint8_t>& out)
    {
        size_t tail = tail_.load(std::memory_order_relaxed);
        size_t head = head_.load(std::memory_order_acquire);

        if (tail == head)
            return false;

        size_t header_size = sizeof(uint32_t);
        size_t read_pos = tail % capacity_;
        uint32_t len;
        uint8_t * pLen = (uint8_t*)(&len);
        for(int i = 0; i < header_size; i++) {
            pLen[i] = buffer_[read_pos];
            read_pos = (read_pos + 1) % capacity_;
        }

        out.resize(len);
        if (tail + len + header_size > head)
            return false;
        for(int i = 0; i < len; i++) {
            out[i] = buffer_[read_pos];
            read_pos = (read_pos + 1) % capacity_;
        }

        tail_.store(tail + header_size + len, std::memory_order_release);
        return true;
    }

private:
    const size_t capacity_;
    std::vector<uint8_t> buffer_;

    alignas(64) std::atomic<size_t> head_;
    alignas(64) std::atomic<size_t> tail_;
};


int main () {
    SPSCRingBuffer rb(64);

    std::thread producer ( [&] () {
        for(int i = 0; i < 10; i++) {
            char c = 'a'+i;
            std::string msg = std::string(11,c);
            bool good = rb.push(msg.data(), msg.size());
            auto now = std::chrono::system_clock::now();
            auto ts = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());
            printf("[%ld] push return  %d\n", ts.count(), good);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });

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

    producer.join();
    consumer.join();
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
