// MinecraftMobileOptimizer/app/src/main/cpp/utils/ThreadPool.cpp
#include "ThreadPool.h"
#include "Logger.h"
#include <android/log.h>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "ThreadPool", __VA_ARGS__)

namespace mcoptimizer {

ThreadPool::ThreadPool(size_t numThreads) : m_stop(false) {
    LOGI("Creating thread pool with %zu threads", numThreads);
    
    for (size_t i = 0; i < numThreads; ++i) {
        m_workers.emplace_back([this, i] {
            for (;;) {
                std::function<void()> task;
                
                {
                    std::unique_lock<std::mutex> lock(m_queueMutex);
                    m_condition.wait(lock, [this] { return m_stop || !m_tasks.empty(); });
                    
                    if (m_stop && m_tasks.empty()) return;
                    
                    task = std::move(m_tasks.front());
                    m_tasks.pop();
                }
                
                task();
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(m_queueMutex);
        m_stop = true;
    }
    
    m_condition.notify_all();
    
    for (auto& worker : m_workers) {
        worker.join();
    }
    
    LOGI("Thread pool destroyed");
}

void ThreadPool::waitAll() {
    std::unique_lock<std::mutex> lock(m_queueMutex);
    m_condition.wait(lock, [this] { return m_tasks.empty(); });
}

size_t ThreadPool::getQueueSize() const {
    std::unique_lock<std::mutex> lock(m_queueMutex);
    return m_tasks.size();
}

} // namespace mcoptimizer
