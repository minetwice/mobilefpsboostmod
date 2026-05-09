#include "FramePacer.h"
#include "utils/Logger.h"
#include <thread>

namespace MCOptimizer {

FramePacer& FramePacer::getInstance() {
    static FramePacer instance;
    return instance;
}

void FramePacer::initialize() {
    Logger::info("FramePacer", "Initializing frame pacer at %d FPS", m_targetFPS);
    m_frameStart = std::chrono::steady_clock::now();
}

void FramePacer::beginFrame() {
    if (!m_enabled) return;
    m_frameStart = std::chrono::steady_clock::now();
}

void FramePacer::endFrame() {
    if (!m_enabled) return;
    m_frameEnd = std::chrono::steady_clock::now();
    calculateFrameTime();
    waitForNextFrame();
}

void FramePacer::optimize() {
    Logger::info("FramePacer", "Optimizing frame pacing...");
    
    // Dynamic frame rate adjustment based on performance
    if (m_currentFPS < 30.0f && m_targetFPS > 30) {
        m_targetFPS = 30;
        Logger::warning("FramePacer", "Lowering target FPS to 30 for stability");
    } else if (m_currentFPS >= 55.0f && m_targetFPS < 60) {
        m_targetFPS = 60;
        Logger::info("FramePacer", "Increasing target FPS to 60");
    }
}

void FramePacer::setTargetFPS(int fps) {
    if (fps <= 0) return;
    m_targetFPS = fps;
    Logger::info("FramePacer", "Target FPS set to %d", fps);
}

void FramePacer::calculateFrameTime() {
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        m_frameEnd - m_frameStart);
    m_lastFrameTimeMs = duration.count();
    
    if (m_lastFrameTimeMs > 0) {
        m_currentFPS = 1000.0f / static_cast<float>(m_lastFrameTimeMs);
    }
}

void FramePacer::waitForNextFrame() {
    int64_t targetFrameTimeMs = 1000 / m_targetFPS;
    int64_t elapsedMs = m_lastFrameTimeMs;
    
    if (elapsedMs < targetFrameTimeMs) {
        int64_t sleepMs = targetFrameTimeMs - elapsedMs;
        if (sleepMs > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(sleepMs));
        }
    }
}

} // namespace MCOptimizer
