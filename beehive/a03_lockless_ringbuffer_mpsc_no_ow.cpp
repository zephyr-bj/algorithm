struct Slot {
    std::atomic<size_t> seq;
    LogRecord record;
};
class BoundedRingBuffer {
public:
    explicit BoundedRingBuffer(size_t size)
        : size_(size),
          mask_(size - 1),
          buffer_(size),
          head_(0),
          tail_(0) {

        // size must be power of two
        for (size_t i = 0; i < size_; ++i)
            buffer_[i].seq.store(i, std::memory_order_relaxed);
    }

    bool enqueue(LogRecord&& record) {
        size_t pos = head_.fetch_add(1, std::memory_order_relaxed);
        Slot& slot = buffer_[pos & mask_];

        size_t seq;
        while (true) {
            seq = slot.seq.load(std::memory_order_acquire);
            intptr_t diff = (intptr_t)seq - (intptr_t)pos;

           if (diff == 0) break;        // slot free
           if (diff < 0) return false;  // buffer full → drop
        }

        slot.record = std::move(record);
        slot.seq.store(pos + 1, std::memory_order_release);
        return true;
    }

    bool dequeue(LogRecord& out) {
        Slot& slot = buffer_[tail_ & mask_];

        size_t seq = slot.seq.load(std::memory_order_acquire);
        intptr_t diff = (intptr_t)seq - (intptr_t)(tail_ + 1);

        if (diff < 0)
            return false; // empty

        out = std::move(slot.record);
        slot.seq.store(tail_ + size_, std::memory_order_release);
        ++tail_;
        return true;
    }
};

class RingBufferAsyncLogger {
public:
    explicit RingBufferAsyncLogger(size_t capacity)
        : buffer(capacity),
          running(true),
          worker(&RingBufferAsyncLogger::consume, this) {}

    void log(LogLevel level, const std::string& msg) {
        LogRecord r{level, msg, currentTime()};
        buffer.enqueue(std::move(r)); // drop if full
    }

    void shutdown() {
        running = false;
        worker.join();
    }

private:
    void consume() {
        LogRecord r;
        while (running || buffer.dequeue(r)) {
            while (buffer.dequeue(r)) {
                auto formatted = LogFormatter::format(r);
                for (auto& s : sinks)
                    s->write(formatted);
            }
            std::this_thread::yield();
        }
    }

private:
    BoundedRingBuffer buffer;
    std::vector<std::shared_ptr<LogSink>> sinks;
    std::atomic<bool> running;
    std::thread worker;
};
