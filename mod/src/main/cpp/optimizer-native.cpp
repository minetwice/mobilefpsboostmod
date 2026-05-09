// MinecraftMobileOptimizer/mod/src/main/cpp/optimizer-native.cpp
#include "optimizer-native.h"
#include <atomic>

namespace mcoptimizer {

static std::atomic<int> g_fps(60);
static std::atomic<int> g_renderDistance(12);
static std::atomic<int> g_entityCount(0);
static std::atomic<int> g_frameCount(0);
static std::atomic<bool> g_frameStarted(false);

void notifyFrameStart() {
    g_frameStarted = true;
    g_frameCount++;
}

void notifyFrameEnd() {
    g_frameStarted = false;
}

void setRenderDistance(int distance) {
    g_renderDistance = distance;
}

void setEntityCount(int count) {
    g_entityCount = count;
}

int getRecommendedRenderDistance() {
    int fps = g_fps.load();
    if (fps < 20) return 4;
    if (fps < 30) return 6;
    if (fps < 45) return 8;
    if (fps < 60) return 10;
    return 12;
}

bool shouldReduceQuality() {
    return g_fps.load() < 30 || g_entityCount.load() > 100;
}

} // namespace mcoptimizer
