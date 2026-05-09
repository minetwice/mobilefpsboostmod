// MinecraftMobileOptimizer/app/src/main/cpp/utils/Timer.h
#pragma once

#include <chrono>

namespace mcoptimizer {

class Timer {
public:
    Timer();
    
    void start();
    void stop();
    void reset();
    
    double elapsedMs() const;
    double elapsedSec() const;
    double elapsedMicro() const;
    
private:
    std::chrono::high_resolution_clock::time_point m_start;
    std::chrono::high_resolution_clock::time_point m_end;
    bool m_running;
};

class ScopedTimer {
public:
    explicit ScopedTimer(const char* name);
    ~ScopedTimer();
private:
    const char* m_name;
    Timer m_timer;
};

} // namespace mcoptimizer
