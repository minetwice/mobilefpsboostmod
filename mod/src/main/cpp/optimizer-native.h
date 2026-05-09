// MinecraftMobileOptimizer/mod/src/main/cpp/optimizer-native.h
#pragma once

namespace mcoptimizer {

void notifyFrameStart();
void notifyFrameEnd();
void setRenderDistance(int distance);
void setEntityCount(int count);
int getRecommendedRenderDistance();
bool shouldReduceQuality();

} // namespace mcoptimizer
