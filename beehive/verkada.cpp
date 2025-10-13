#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <vector>
#include <cstdlib>
#include <chrono>

struct als_sta {
    als_sta(uint32_t s, float l, uint64_t t):status(s), lux(l), timestamp(t) {};
    uint32_t status;
    float lux;
    uint64_t timestamp;
};
const static uint32_t no_action = 0;
struct lm {
    lm(float l, uint64_t t):lux(l), timestamp(t) {};
    float lux;
    uint64_t timestamp;
};

class als {
public:
    als():stop(false),thd(&als::recordALS, this) {};
    ~als();
private:
    struct als_sta als_read(); //blocking
    std::vector<lm> lux;
    std::mutex mtx;
    std::condition_variable cv;
    std::thread thd;
    std::atomic<bool> stop;
    void recordALS();
public:
    float als_read_cur(); //noblocking
    float als_read_prv(uint64_t t); //noblocking
};

als::~als() {
    stop = true;
    thd.join();
    std::unique_lock<std::mutex>lk(mtx);
    int sz = lux.size();
    lux.clear();
    printf("als quit, %d data points recorded\n", sz);
}
static uint64_t t0 = 0;
struct als_sta als::als_read() {
    float reading = rand();
    als_sta as(1, reading, t0++);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return as;
}


void als::recordALS() {
    while(stop == false) {
        {
            struct als_sta cur = als_read();
            if (cur.status != no_action) {
                std::unique_lock<std::mutex> lk(mtx);
                lux.push_back(lm(cur.lux, cur.timestamp));
            }
        }
        cv.notify_all();
    }
}

float als::als_read_cur() {
    float res = 0;
    {
        std::unique_lock<std::mutex>lk(mtx);
        res = lux.back().lux;
    }
    cv.notify_one();
    return res;
}

float als::als_read_prv(uint64_t t) {

    int a = 0; 
    int b = 0;
    {
        std::unique_lock<std::mutex>lk(mtx);
        b = lux.size() - 1;
    }
    while(a<b) {
        uint64_t m = lux[a].timestamp + (lux[b].timestamp - lux[a].timestamp)/2;
        if (t > m) {
            a = a + (b-a)/2 + 1;
        } else {
            b = m;
        }
    }
    printf("looking for %ld, return record at %ld\n", t, lux[a].timestamp);
    return lux[a].lux;
}

int main() {
    als obj;

    std::this_thread::sleep_for(std::chrono::seconds(5));
    float cur_als = obj.als_read_cur();
    printf("cur_als = %f\n", cur_als);
    std::this_thread::sleep_for(std::chrono::seconds(5));
    cur_als = obj.als_read_prv(4);
    printf("prv_als = %f\n", cur_als);
    cur_als = obj.als_read_cur();
    printf("cur_als = %f\n", cur_als);
    return 0;
}







