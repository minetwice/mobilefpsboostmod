// MinecraftMobileOptimizer/app/src/main/cpp/utils/ThreadPool.h
#pragma once

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>

namespace mcoptimizer {

class ThreadPool {
public:
    explicit ThreadPool(size_t numThreads);
    ~ThreadPool();
    
    template<typename F, typename... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type>;
    
    void waitAll();
    size_t getQueueSize() const;
    
private:
    std::vector<std::thread> m_workers;
    std::queue<std::function<void()>> m_tasks;
    
    mutable std::mutex m_queueMutex;
    std::condition_variable m_condition;
    bool m_stop;
};

} // namespace mcoptimizer
