#ifndef FRAME_PACER_H
#define FRAME_PACER_H

#include <chrono>
#include <cstdint>

namespace MCOptimizer {

class FramePacer {
public:
    static FramePacer& getInstance();
    
    void initialize();
    void beginFrame();
    void endFrame();
    void optimize();
    
    void setTargetFPS(int fps);
    int getTargetFPS() const { return m_targetFPS; }
    
    int64_t getLastFrameTime() const { return m_lastFrameTimeMs; }
    float getCurrentFPS() const { return m_currentFPS; }
    
    void setEnabled(bool enabled) { m_enabled = enabled; }
    bool isEnabled() const { return m_enabled; }
    
private:
    FramePacer() = default;
    ~FramePacer() = default;
    FramePacer(const FramePacer&) = delete;
    FramePacer& operator=(const FramePacer&) = delete;
    
    void calculateFrameTime();
    void waitForNextFrame();
    
    int m_targetFPS = 60;
    int64_t m_lastFrameTimeMs = 0;
    float m_currentFPS = 60.0f;
    bool m_enabled = true;
    
    std::chrono::steady_clock::time_point m_frameStart;
    std::chrono::steady_clock::time_point m_frameEnd;
};

} // namespace MCOptimizer

#endif // FRAME_PACER_H
