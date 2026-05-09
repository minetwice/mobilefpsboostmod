// MinecraftMobileOptimizer/app/src/main/cpp/optimizer/FramePacer.h
#pragma once
#include <chrono>

class FramePacer {
public:
    explicit FramePacer(int targetFps);
    ~FramePacer();
    void beginFrame();
    void endFrame();
    int getCurrentFps() const;
    float getFrameTimeMs() const;
    void setTargetFps(int fps);
private:
    int targetFps_;
    float targetFrameTimeMs_;
    std::chrono::high_resolution_clock::time_point frameStart_;
    std::chrono::high_resolution_clock::time_point lastFrameTime_;
    int frameCount_ = 0;
    int currentFps_ = 0;
    float frameTimeMs_ = 0.0f;
    std::chrono::high_resolution_clock::time_point fpsUpdateTime_;
};
