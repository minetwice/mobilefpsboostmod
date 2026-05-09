// MinecraftMobileOptimizer/app/src/main/cpp/utils/Timer.cpp
#include "Timer.h"
#include "Logger.h"
#include <android/log.h>

namespace mcoptimizer {

Timer::Timer() : m_running(false) {}

void Timer::start() {
    m_start = std::chrono::high_resolution_clock::now();
    m_running = true;
}

void Timer::stop() {
    m_end = std::chrono::high_resolution_clock::now();
    m_running = false;
}

void Timer::reset() {
    m_running = false;
}

double Timer::elapsedMs() const {
    auto end = m_running ? std::chrono::high_resolution_clock::now() : m_end;
    return std::chrono::duration<double, std::milli>(end - m_start).count();
}

double Timer::elapsedSec() const {
    return elapsedMs() / 1000.0;
}

double Timer::elapsedMicro() const {
    auto end = m_running ? std::chrono::high_resolution_clock::now() : m_end;
    return std::chrono::duration<double, std::micro>(end - m_start).count();
}

// ScopedTimer
ScopedTimer::ScopedTimer(const char* name) : m_name(name) {
    m_timer.start();
}

ScopedTimer::~ScopedTimer() {
    m_timer.stop();
    LOG_DEBUG("%s took %.3f ms", m_name, m_timer.elapsedMs());
}

} // namespace mcoptimizer
