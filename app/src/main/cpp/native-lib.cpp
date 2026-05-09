// MinecraftMobileOptimizer/app/src/main/cpp/native-lib.cpp
// JNI Bridge - Main entry point for Android

#include <jni.h>
#include <android/log.h>
#include <string>
#include <memory>

#include "core/Engine.h"
#include "renderer/VulkanRenderer.h"
#include "optimizer/FramePacer.h"
#include "optimizer/MemoryPool.h"
#include "optimizer/TextureCache.h"
#include "hooks/GLHooks.h"
#include "hooks/EGLHooks.h"
#include "utils/Logger.h"

#define LOG_TAG "MCOptimizer"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

// Global engine instance
static std::unique_ptr<mcoptimizer::Engine> g_engine = nullptr;

extern "C" {

// ==================== ENGINE LIFECYCLE ====================

JNIEXPORT void JNICALL
Java_com_mcoptimizer_jni_NativeBridge_initOptimizer(JNIEnv* env, jobject thiz, jint targetFps) {
    LOGI("╔══════════════════════════════════════╗");
    LOGI("║  MC Optimizer v1.0.0                 ║");
    LOGI("║  Minecraft 1.21.11 | Java 21         ║");
    LOGI("╚══════════════════════════════════════╝");
    LOGI("Initializing with target FPS: %d", targetFps);
    
    try {
        g_engine = std::make_unique<mcoptimizer::Engine>();
        g_engine->initialize(targetFps);
        LOGI("Engine initialized successfully");
    } catch (const std::exception& e) {
        LOGE("Engine initialization failed: %s", e.what());
    }
}

JNIEXPORT void JNICALL
Java_com_mcoptimizer_jni_NativeBridge_shutdown(JNIEnv* env, jobject thiz) {
    LOGI("Shutting down MC Optimizer...");
    g_engine.reset();
    LOGI("Shutdown complete");
}

// ==================== FRAME MANAGEMENT ====================

JNIEXPORT void JNICALL
Java_com_mcoptimizer_jni_NativeBridge_beginFrame(JNIEnv* env, jobject thiz) {
    if (g_engine) {
        g_engine->beginFrame();
    }
}

JNIEXPORT void JNICALL
Java_com_mcoptimizer_jni_NativeBridge_endFrame(JNIEnv* env, jobject thiz) {
    if (g_engine) {
        g_engine->endFrame();
    }
}

// ==================== RENDER CONTROL ====================

JNIEXPORT void JNICALL
Java_com_mcoptimizer_jni_NativeBridge_setRenderScale(JNIEnv* env, jobject thiz, jfloat scale) {
    LOGD("Setting render scale: %.3f", scale);
    if (g_engine) {
        g_engine->setRenderScale(scale);
    }
}

JNIEXPORT jfloat JNICALL
Java_com_mcoptimizer_jni_NativeBridge_getRenderScale(JNIEnv* env, jobject thiz) {
    return g_engine ? g_engine->getRenderScale() : 1.0f;
}

// ==================== PERFORMANCE ====================

JNIEXPORT jint JNICALL
Java_com_mcoptimizer_jni_NativeBridge_getCurrentFps(JNIEnv* env, jobject thiz) {
    return g_engine ? g_engine->getCurrentFps() : 0;
}

JNIEXPORT jfloat JNICALL
Java_com_mcoptimizer_jni_NativeBridge_getFrameTimeMs(JNIEnv* env, jobject thiz) {
    return g_engine ? g_engine->getFrameTimeMs() : 0.0f;
}

JNIEXPORT void JNICALL
Java_com_mcoptimizer_jni_NativeBridge_setTargetFps(JNIEnv* env, jobject thiz, jint fps) {
    LOGI("Changing target FPS to: %d", fps);
    if (g_engine) {
        g_engine->setTargetFps(fps);
    }
}

// ==================== MEMORY ====================

JNIEXPORT void JNICALL
Java_com_mcoptimizer_jni_NativeBridge_optimizeMemory(JNIEnv* env, jobject thiz) {
    LOGI("Manual memory optimization triggered");
    if (g_engine) {
        g_engine->optimizeMemory();
    }
}

JNIEXPORT jlong JNICALL
Java_com_mcoptimizer_jni_NativeBridge_getUsedMemory(JNIEnv* env, jobject thiz) {
    return g_engine ? g_engine->getUsedMemory() : 0;
}

JNIEXPORT jlong JNICALL
Java_com_mcoptimizer_jni_NativeBridge_getFreeMemory(JNIEnv* env, jobject thiz) {
    return g_engine ? g_engine->getFreeMemory() : 0;
}

// ==================== HOOKS ====================

JNIEXPORT void JNICALL
Java_com_mcoptimizer_jni_NativeBridge_installGLHooks(JNIEnv* env, jobject thiz) {
    LOGI("Installing OpenGL hooks...");
    mcoptimizer::GLHooks::install();
}

JNIEXPORT void JNICALL
Java_com_mcoptimizer_jni_NativeBridge_removeGLHooks(JNIEnv* env, jobject thiz) {
    LOGI("Removing OpenGL hooks...");
    mcoptimizer::GLHooks::remove();
}

JNIEXPORT void JNICALL
Java_com_mcoptimizer_jni_NativeBridge_installEGLHooks(JNIEnv* env, jobject thiz) {
    LOGI("Installing EGL hooks...");
    mcoptimizer::EGLHooks::install();
}

// ==================== DEBUG ====================

JNIEXPORT jstring JNICALL
Java_com_mcoptimizer_jni_NativeBridge_getEngineInfo(JNIEnv* env, jobject thiz) {
    std::string info = "MC Optimizer v1.0.0\n";
    info += "Minecraft: 1.21.11\n";
    info += "Java: 21\n";
    info += "Native: C++17\n";
    
    if (g_engine) {
        info += "Engine: Active\n";
        info += "FPS: " + std::to_string(g_engine->getCurrentFps()) + "\n";
    } else {
        info += "Engine: Inactive\n";
    }
    
    return env->NewStringUTF(info.c_str());
}

JNIEXPORT void JNICALL
Java_com_mcoptimizer_jni_NativeBridge_setLogLevel(JNIEnv* env, jobject thiz, jint level) {
    mcoptimizer::Logger::setLevel(static_cast<mcoptimizer::LogLevel>(level));
}

} // extern "C"
