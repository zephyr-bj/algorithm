class LockFreeMPSCQueue {
public:
    LockFreeMPSCQueue() {
        head = tail = new Node(LogRecord{});
    }

    ~LockFreeMPSCQueue() {
        while (tail) {
            Node* next = tail->next.load();
            delete tail;
            tail = next;
        }
    }

    // Producers
    void enqueue(LogRecord record) {
        Node* node = new Node(std::move(record));
        Node* prev = head.exchange(node, std::memory_order_acq_rel);
        prev->next.store(node, std::memory_order_release);
    }

    // Single consumer
    bool dequeue(LogRecord& out) {
        Node* next = tail->next.load(std::memory_order_acquire);
        if (!next) return false;

        out = std::move(next->record);
        delete tail;
        tail = next;
        return true;
    }

private:
    std::atomic<Node*> head; // producers push here
    Node* tail;              // consumer pops here
};

// Lock free logger
class LockFreeAsyncLogger {
public:
    static LockFreeAsyncLogger& instance() {
        static LockFreeAsyncLogger logger;
        return logger;
    }

    void addSink(std::shared_ptr<LogSink> sink) {
        sinks.push_back(sink);
    }

    void setLevel(LogLevel level) {
        minLevel.store(level, std::memory_order_relaxed);
    }

    void log(LogLevel level, const std::string& msg) {
        if (level < minLevel.load(std::memory_order_relaxed)) return;

        LogRecord record{level, msg, currentTime()};
        queue.enqueue(std::move(record));
    }

    void shutdown() {
        running.store(false);
        if (worker.joinable())
            worker.join();
    }

private:
    LockFreeAsyncLogger()
        : running(true),
          worker(&LockFreeAsyncLogger::consume, this) {}

    ~LockFreeAsyncLogger() {
        shutdown();
    }

    void consume() {
        while (running.load() || drain()) {
            LogRecord record;
            while (queue.dequeue(record)) {
                std::string formatted = LogFormatter::format(record);
                for (auto& sink : sinks)
                    sink->write(formatted);
            }
            std::this_thread::yield(); // reduce CPU burn
        }
    }

    bool drain() {
        LogRecord r;
        return queue.dequeue(r);
    }

    std::string currentTime() {
        std::time_t t = std::time(nullptr);
        char buf[32];
        std::strftime(buf, sizeof(buf),
                      "%Y-%m-%d %H:%M:%S",
                      std::localtime(&t));
        return buf;
    }

private:
    LockFreeMPSCQueue queue;
    std::vector<std::shared_ptr<LogSink>> sinks;
    std::thread worker;
    std::atomic<bool> running;
    std::atomic<LogLevel> minLevel{LogLevel::INFO};
};

