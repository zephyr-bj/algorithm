#include <atomic>
#include <vector>
#include <chrono>
#include <thread>
#include <utility>

template <class T>
class ringBuf {
private:
    std::atomic<uint32_t> head_;
    std::atomic<uint32_t> tail_;
    const uint32_t cap_;
    std::vector<T> buf_;
public:
    ringBuf(size_t size):
    cap_(size),
    buf_(size),
    head_(0),
    tail_(0) {
        
    }
    bool push(T && data) {
        uint32_t head = head_.load(std::memory_order_relaxed);
        uint32_t tail = tail_.load(std::memory_order_acquire);
        if (head-tail==cap_)
            return false;
        uint32_t index = head % cap_;
        buf_[index] = std::move(data);
        head_.store(head+1, std::memory_order_release);
        return true;
    }
    bool pop(T & data) {
        uint32_t tail = tail_.load(std::memory_order_relaxed);
        uint32_t head = head_.load(std::memory_order_acquire);
        if (head == tail)
            return false;
        uint32_t index = tail % cap_;
        data = std::move(buf_[index]);
        tail_.store(tail+1, std::memory_order_release);
        return true;
    }
};

struct testNode {
    uint32_t x;
    uint32_t y;
    uint32_t z;
    testNode(){}
    testNode(uint32_t a, uint32_t b, uint32_t c):x(a),y(b),z(c) {}
};

int main()
{
    ringBuf<testNode> myrb(8);
    
    std::thread producer ([&]() {
        for(int i = 0; i < 12; i++) {
            testNode input(i, i + 1, i + 2);
            bool good = myrb.push(input);
            //requires right value reference: T&& data
            //bool good = myrb.push(testNode(i, i + 1, i + 2));
            if (good) {
                printf("input %d good\n", i);
            } else {
                printf("input %d failed\n", i);
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });
    
    std::thread consumer ([&]() {
        for(int i = 0; i < 12; i++) {
            testNode output;
            bool good = myrb.pop(output);
            if (good) {
                printf("ouptpu[%d]: [%d, %d, %d] good\n", i, output.x, output.y, output.z);
            } else {
                printf("output[%d]: failed\n", i);
            }
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    });
    consumer.join();
    producer.join();
    

    return 0;
}
