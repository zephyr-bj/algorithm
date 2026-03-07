#include <atomic>
#include <chrono>
#include <algorithm>

class LockFreeRateLimiter {
private:
    struct State {
        double tokens;
        double last_update; // Seconds since epoch
    };

    std::atomic<State> state;
    const double capacity;
    const double refill_rate;

    // Helper to get current time in seconds
    double get_now() const {
        auto now = std::chrono::steady_clock::now().time_since_epoch();
        return std::chrono::duration<double>(now).count();
    }

public:
    LockFreeRateLimiter(double max_tokens, double refill_per_sec)
        : capacity(max_tokens), refill_rate(refill_per_sec) {
        state.store({max_tokens, get_now()});
    }

    bool allow_request(double requested = 1.0) {
        State current_state = state.load(std::memory_order_relaxed);
        State next_state;

        do {
            double now = get_now();
            double elapsed = now - current_state.last_update;
            
            // Calculate new token count
            double refreshed_tokens = std::min(capacity, 
                current_state.tokens + (elapsed * refill_rate));

            if (refreshed_tokens < requested) {
                return false; // Not enough tokens
            }

            next_state.tokens = refreshed_tokens - requested;
            next_state.last_update = now;

            // CAS: Try to update the state. If another thread changed 'state' 
            // in the meantime, current_state is updated and we loop again.
        } while (!state.compare_exchange_weak(current_state, next_state,
                                              std::memory_order_release,
                                              std::memory_order_relaxed));

        return true;
    }
};

/*
No Context Switching: Unlike a mutex, which might put a thread to sleep (kernel transition), 
the CAS loop keeps the CPU active. This is much faster for "low contention" but can spike 
CPU usage if hundreds of threads collide on the same memory address.

Memory Ordering: I used std::memory_order_release and relaxed. In high-performance C++, 
we fine-tune how CPU caches synchronize. release ensures that when we write the new state, 
other threads see the most recent time calculation.

The "Weak" CAS: compare_exchange_weak is used here because it’s allowed to fail 
spuriously (even if the value didn't change) on some architectures like ARM. In a loop, 
it's actually more efficient than compare_exchange_strong.

Implementation Note
For the code above to compile, State must be "trivially copyable" and fit within the 
size of an atomic type (usually 16 bytes on 64-bit systems). 
If your compiler complains about std::atomic<State>, you may need to ensure 
your platform supports Double-Width CAS (often called cmpxchg16b on x86).
*/
