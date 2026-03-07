#include <iostream>
#include <chrono>
#include <mutex>
#include <algorithm>

class RateLimiter {
private:
    double capacity;
    double tokens;
    double refill_rate; // tokens per second
    std::chrono::steady_clock::time_point last_refill_time;
    std::mutex mtx;

public:
    RateLimiter(double max_tokens, double refill_per_second)
        : capacity(max_tokens), tokens(max_tokens), refill_rate(refill_per_second) {
        last_refill_time = std::chrono::steady_clock::now();
    }

    bool allow_request(double tokens_requested = 1.0) {
        std::lock_guard<std::mutex> lock(mtx);
        
        // 1. Calculate elapsed time and refill
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = now - last_refill_time;
        
        // 2. Add tokens based on time passed
        tokens = std::min(capacity, tokens + (elapsed.count() * refill_rate));
        last_refill_time = now;

        // 3. Check if we have enough tokens
        if (tokens >= tokens_requested) {
            tokens -= tokens_requested;
            return true;
        }

        return false; // Rate limit exceeded
    }
};
