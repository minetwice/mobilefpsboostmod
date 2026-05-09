// MinecraftMobileOptimizer/app/src/main/cpp/optimizer/FramePacer.cpp
#include "FramePacer.h"
#include <thread>
#include <android/log.h>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "FramePacer", __VA_ARGS__)

FramePacer::FramePacer(int targetFps) 
    : targetFps_(targetFps)
    , targetFrameTimeMs_(1000.0f / targetFps)
    , fpsUpdateTime_(std::chrono::high_resolution_clock::now()) {
    LOGI("Target FPS: %d (%.2f ms/frame)", targetFps, targetFrameTimeMs_);
}

FramePacer::~FramePacer() = default;

void FramePacer::beginFrame() {
    frameStart_ = std::chrono::high_resolution_clock::now();
}

void FramePacer::endFrame() {
    auto frameEnd = std::chrono::high_resolution_clock::now();
    frameTimeMs_ = std::chrono::duration<float, std::milli>(frameEnd - frameStart_).count();
    
    frameCount_++;
    auto now = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration<float>(now - fpsUpdateTime_).count();
    
    if (elapsed >= 1.0f) {
        currentFps_ = frameCount_;
        frameCount_ = 0;
        fpsUpdateTime_ = now;
        LOGI("FPS: %d | Frame: %.2f ms", currentFps_, frameTimeMs_);
    }
    
    if (frameTimeMs_ < targetFrameTimeMs_) {
        float sleepMs = targetFrameTimeMs_ - frameTimeMs_;
        std::this_thread::sleep_for(std::chrono::microseconds(static_cast<int>(sleepMs * 1000)));
    }
}

int FramePacer::getCurrentFps() const { return currentFps_; }
float FramePacer::getFrameTimeMs() const { return frameTimeMs_; }

void FramePacer::setTargetFps(int fps) {
    targetFps_ = fps;
    targetFrameTimeMs_ = 1000.0f / fps;
}
