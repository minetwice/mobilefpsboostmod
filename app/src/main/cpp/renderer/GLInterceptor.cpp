// MinecraftMobileOptimizer/app/src/main/cpp/renderer/GLInterceptor.cpp
#include "GLInterceptor.h"
#include <android/log.h>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "GLInterceptor", __VA_ARGS__)

namespace GLInterceptor {

static bool cullingEnabled = true;
static bool batchingEnabled = true;
static bool lodEnabled = true;
static int drawCallCount = 0;
static int vertexCount = 0;
static unsigned int lastBoundTexture = 0;
static unsigned int lastUsedProgram = 0;

void initialize() {
    LOGI("GL Interceptor init - MC 1.21.11");
    resetStats();
}

void shutdown() { LOGI("GL Interceptor shutdown"); }

void onDrawArrays(int mode, int first, int count) {
    drawCallCount++;
    vertexCount += count;
}

void onDrawElements(int mode, int count, int type, const void* indices) {
    drawCallCount++;
    vertexCount += count;
}

void onBindTexture(unsigned int texture) {
    if (texture == lastBoundTexture) return;
    lastBoundTexture = texture;
}

void onUseProgram(unsigned int program) {
    if (program == lastUsedProgram) return;
    lastUsedProgram = program;
}

void setCullingEnabled(bool enabled) { cullingEnabled = enabled; }
void setBatchingEnabled(bool enabled) { batchingEnabled = enabled; }
void setLODEnabled(bool enabled) { lodEnabled = enabled; }

int getDrawCallCount() { return drawCallCount; }
int getVertexCount() { return vertexCount; }
void resetStats() { drawCallCount = 0; vertexCount = 0; }

} // namespace GLInterceptor
