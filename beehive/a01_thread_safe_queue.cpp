#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class BlockingQueue {
public:
    void push(T item) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(std::move(item));
        cv_.notify_one();
    }

    bool pop(T& item) {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [&] { return !queue_.empty() || stop_; });

        if (queue_.empty()) return false;

        item = std::move(queue_.front());
        queue_.pop();
        return true;
    }

    void stop() {
        std::lock_guard<std::mutex> lock(mutex_);
        stop_ = true;
        cv_.notify_all();
    }

private:
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable cv_;
    bool stop_ = false;
};

// Logger code below
#include <thread>
#include <atomic>

class AsyncLogger {
public:
    static AsyncLogger& instance() {
        static AsyncLogger logger;
        return logger;
    }

    void addSink(std::shared_ptr<LogSink> sink) {
        sinks.push_back(sink);
    }

    void setLevel(LogLevel level) {
        minLevel = level;
    }

    void log(LogLevel level, const std::string& msg) {
        if (level < minLevel) return;

        LogRecord record{level, msg, currentTime()};
        queue.push(std::move(record));
    }

    // Convenience
    void info(const std::string& msg) { log(LogLevel::INFO, msg); }
    void error(const std::string& msg) { log(LogLevel::ERROR, msg); }

    void shutdown() {
        running = false;
        queue.stop();
        if (worker.joinable())
            worker.join();
    }

private:
    AsyncLogger()
        : running(true),
          worker(&AsyncLogger::process, this) {}

    ~AsyncLogger() {
        shutdown();
    }

    void process() {
        while (running) {
            LogRecord record;
            if (!queue.pop(record)) break;

            std::string formatted = LogFormatter::format(record);
            for (auto& sink : sinks) {
                sink->write(formatted);
            }
        }
    }

    std::string currentTime() {
        std::time_t now = std::time(nullptr);
        char buf[32];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S",
                      std::localtime(&now));
        return buf;
    }

private:
    BlockingQueue<LogRecord> queue;
    std::vector<std::shared_ptr<LogSink>> sinks;
    std::thread worker;
    std::atomic<bool> running;
    LogLevel minLevel = LogLevel::INFO;
};

