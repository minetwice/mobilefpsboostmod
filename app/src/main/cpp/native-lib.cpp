// MinecraftMobileOptimizer/app/src/main/cpp/native-lib.cpp
#include <jni.h>
#include <android/log.h>
#include <string>
#include <chrono>
#include <thread>

#include "renderer/VulkanRenderer.h"
#include "optimizer/FramePacer.h"
#include "optimizer/MemoryPool.h"
#include "utils/Logger.h"

#define LOG_TAG "MCOptimizer"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

static FramePacer* g_framePacer = nullptr;
static MemoryPool* g_memoryPool = nullptr;
static VulkanRenderer* g_renderer = nullptr;

extern "C" {

JNIEXPORT void JNICALL
Java_com_mcoptimizer_jni_NativeBridge_initOptimizer(JNIEnv* env, jobject thiz, jint targetFps) {
    LOGI("Initializing MC Optimizer v1.0.0 for MC 1.21.11 | Target FPS: %d", targetFps);
    
    g_framePacer = new FramePacer(targetFps);
    g_memoryPool = new MemoryPool(512 * 1024 * 1024);
    g_renderer = new VulkanRenderer();
    g_renderer->initialize();
    
    LOGI("Optimizer initialized - Java 21 compatible");
}

JNIEXPORT void JNICALL
Java_com_mcoptimizer_jni_NativeBridge_beginFrame(JNIEnv* env, jobject thiz) {
    if (g_framePacer) g_framePacer->beginFrame();
}

JNIEXPORT void JNICALL
Java_com_mcoptimizer_jni_NativeBridge_endFrame(JNIEnv* env, jobject thiz) {
    if (g_framePacer) g_framePacer->endFrame();
}

JNIEXPORT void JNICALL
Java_com_mcoptimizer_jni_NativeBridge_optimizeMemory(JNIEnv* env, jobject thiz) {
    if (g_memoryPool) {
        g_memoryPool->defragment();
        g_memoryPool->releaseUnused();
    }
}

JNIEXPORT void JNICALL
Java_com_mcoptimizer_jni_NativeBridge_setRenderScale(JNIEnv* env, jobject thiz, jfloat scale) {
    if (g_renderer) g_renderer->setRenderScale(scale);
}

JNIEXPORT jint JNICALL
Java_com_mcoptimizer_jni_NativeBridge_getCurrentFps(JNIEnv* env, jobject thiz) {
    return g_framePacer ? g_framePacer->getCurrentFps() : 0;
}

JNIEXPORT void JNICALL
Java_com_mcoptimizer_jni_NativeBridge_shutdown(JNIEnv* env, jobject thiz) {
    LOGI("Shutting down MC Optimizer");
    delete g_renderer; g_renderer = nullptr;
    delete g_framePacer; g_framePacer = nullptr;
    delete g_memoryPool; g_memoryPool = nullptr;
}

} // extern "C"
