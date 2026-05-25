#include <atomic>
#include <condition_variable>
#include <deque>
#include <mutex>
#include <thread>
#include <iostream>

class SpinLock {
    std::atomic_flag flag = ATOMIC_FLAG_INIT;

public:
    void lock() {
        while (flag.test_and_set(std::memory_order_acquire)) {
            std::this_thread::yield();
        }
    }

    void unlock() {
        flag.clear(std::memory_order_release);
    }
};

class KernelMutexSim {
private:
    struct Waiter {
        std::condition_variable cv;
        std::mutex cv_mtx;
        bool woken = false;
    };
    
    void schedule_block(Waiter& w) {
        std::unique_lock<std::mutex> lk(w.cv_mtx);
    
        w.cv.wait(lk, [&] {
            return w.woken;
        });
    
        w.woken = false; // optional: reset if reused
    }
    
    void schedule_wakeup(Waiter* w) {
        {
            std::lock_guard<std::mutex> lk(w->cv_mtx);
            w->woken = true;
        }
    
        w->cv.notify_one();
    }
    std::atomic<std::thread::id> owner;
    SpinLock wait_lock;
    std::deque<Waiter*> waiters;

public:
    KernelMutexSim() : owner(std::thread::id{}) {}
    void mutex_lock() {
        std::thread::id self = std::this_thread::get_id();
        std::thread::id nobody{};
    
        // Fast path: uncontended acquire
        // 1. we do not want to retry if failed, we just sleep, 
        //    so we use compare_exchange_strong
        // 2. we do not use the 'loop + compare_exchange_weak',
        //    cz the owner may hold it for a long time
        // 3. we do not use a single 'compare_exchange_weak',
        //    cz it may give spurious failure.
        if (owner.compare_exchange_strong(
                nobody,
                self,
                std::memory_order_acquire,
                std::memory_order_relaxed)) {
            return;
        }
    
        Waiter waiter;
    
        while (true) {
            wait_lock.lock();
    
            nobody = std::thread::id{};
    
            if (owner.compare_exchange_strong(
                    nobody,
                    self,
                    std::memory_order_acquire,
                    std::memory_order_relaxed)) {
                wait_lock.unlock();
                return;
            }
    
            waiters.push_back(&waiter);
    
            wait_lock.unlock();
    
            schedule_block(waiter);
        }
    }

    void mutex_unlock() {
        std::thread::id self = std::this_thread::get_id();
    
        if (owner.load(std::memory_order_relaxed) != self) {
            throw std::runtime_error("mutex_unlock by non-owner");
        }
    
        wait_lock.lock();
    
        if (waiters.empty()) {
            owner.store(std::thread::id{}, std::memory_order_release);
            wait_lock.unlock();
            return;
        }
    
        Waiter* waiter = waiters.front();
        waiters.pop_front();
    
        owner.store(std::thread::id{}, std::memory_order_release);
    
        wait_lock.unlock();
    
        schedule_wakeup(waiter);
    }
};

KernelMutexSim kmutex;
int shared_counter = 0;

void worker() {
    for (int i = 0; i < 10000; i++) {
        kmutex.mutex_lock();

        shared_counter++;

        kmutex.mutex_unlock();
    }
}

int main() {
    std::thread t1(worker);
    std::thread t2(worker);
    std::thread t3(worker);

    t1.join();
    t2.join();
    t3.join();

    std::cout << "counter = " << shared_counter << "\n";
}
