#include <iostream>
#include <vector>
#include <list>
#include <atomic>
#include <optional>
#include <thread>

// g++ scsp_2list.cpp -std=c++17 -o scsp -pthread

struct FrameBuffer {
    int id;
    size_t length;
};

class V4L2DeviceFineGrained {
private:
    int capacity;
    std::vector<FrameBuffer> all_buffers;
    
    // List 1: Controlled by the hardware incoming queue
    std::list<int> queued_list; 
    std::atomic_flag queued_lock = ATOMIC_FLAG_INIT; // Protects queued_list

    // List 2: Controlled by the finished/ready queue
    std::list<int> done_list;   
    std::atomic_flag done_lock = ATOMIC_FLAG_INIT;   // Protects done_list

    // Spinlock helper helpers
    void lock(std::atomic_flag& spinlock) {
        while (spinlock.test_and_set(std::memory_order_acquire)) {
#if defined(__x86_64__) || defined(_M_X64)
            asm volatile("pause" ::: "memory");
#endif
        }
    }

    void unlock(std::atomic_flag& spinlock) {
        spinlock.clear(std::memory_order_release);
    }

public:
    V4L2DeviceFineGrained(int count) : capacity(count) {
        for (int i = 0; i < count; ++i) {
            all_buffers.push_back({i, 1024 * 1024});
        }
    }

    void qbuf(int buffer_id) {
        lock(queued_lock); // Only lock the incoming list
        std::cout << "[QBUF] App pushing buffer " << buffer_id << " to queued_list.\n";
        queued_list.push_back(buffer_id);
        unlock(queued_lock);
    }

    void hardware_interrupt_handler() {
        int buf_id = -1;

        lock(queued_lock);
        if (!queued_list.empty()) {
            buf_id = queued_list.front();
            queued_list.pop_front();
        }
        unlock(queued_lock);

        if (buf_id != -1) {
            lock(done_lock); // Only lock the outgoing list
            std::cout << "[ISR] Hardware moving buffer " << buf_id << " to done_list.\n";
            done_list.push_back(buf_id);
            unlock(done_lock);
        }
    }

    std::optional<int> dqbuf_nonblocking() {
        lock(done_lock); // Only lock the outgoing list

        if (done_list.empty()) {
            unlock(done_lock);
            return std::nullopt; 
        }

        int buf_id = done_list.front();
        done_list.pop_front();
        
        unlock(done_lock);
        std::cout << "[DQBUF] App pull buffer " << buf_id << " from done_list.\n";
        return buf_id;
    }
};

int main() {
    V4L2DeviceFineGrained camera(5);

    camera.qbuf(0);
    camera.qbuf(1);

    std::thread producer([&](){
        for(int i = 0; i < 10; i++) {
            camera.hardware_interrupt_handler();
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
        }
    });
    std::thread consumer([&](){
        for(int i = 0; i < 10; i++) { 
            auto frame = camera.dqbuf_nonblocking();
            if (frame != std::nullopt) {
                std::cout << "[Process] work with data in buffer " << frame.value() << " .\n";
                camera.qbuf(frame.value());
            } else {
                std::cout << "[Process] no buffer ready.\n";
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
        }
    });
    producer.join();
    consumer.join();

    return 0;
}
