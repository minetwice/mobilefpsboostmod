// MinecraftMobileOptimizer/app/src/main/cpp/renderer/GLInterceptor.h
#pragma once

namespace GLInterceptor {
void initialize();
void shutdown();
void onDrawArrays(int mode, int first, int count);
void onDrawElements(int mode, int count, int type, const void* indices);
void onBindTexture(unsigned int texture);
void onUseProgram(unsigned int program);
void setCullingEnabled(bool enabled);
void setBatchingEnabled(bool enabled);
void setLODEnabled(bool enabled);
int getDrawCallCount();
int getVertexCount();
void resetStats();
}
