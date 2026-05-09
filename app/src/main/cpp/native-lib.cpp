#include <jni.h>
#include <string>
#include <android/log.h>
#include "renderer/VulkanRenderer.h"
#include "optimizer/FramePacer.h"
#include "optimizer/MemoryPool.h"
#include "utils/Logger.h"

#define LOG_TAG "MCOptimizerJNI"

// Native method implementations
extern "C" {

JNIEXPORT jboolean JNICALL
Java_com_mcoptimizer_jni_NativeBridge_initRenderer(JNIEnv *env, jobject thiz) {
    MCOptimizer::Logger::init();
    MCOptimizer::Logger::info(LOG_TAG, "Initializing renderer...");
    
    bool success = MCOptimizer::VulkanRenderer::getInstance().initialize();
    if (success) {
        MCOptimizer::Logger::info(LOG_TAG, "Renderer initialized successfully");
    } else {
        MCOptimizer::Logger::error(LOG_TAG, "Failed to initialize renderer");
    }
    return success;
}

JNIEXPORT void JNICALL
Java_com_mcoptimizer_jni_NativeBridge_destroyRenderer(JNIEnv *env, jobject thiz) {
    MCOptimizer::Logger::info(LOG_TAG, "Destroying renderer...");
    MCOptimizer::VulkanRenderer::getInstance().destroy();
}

JNIEXPORT void JNICALL
Java_com_mcoptimizer_jni_NativeBridge_setResolution(JNIEnv *env, jobject thiz, 
                                                     jint width, jint height) {
    MCOptimizer::VulkanRenderer::getInstance().setResolution(width, height);
}

JNIEXPORT void JNICALL
Java_com_mcoptimizer_jni_NativeBridge_swapBuffers(JNIEnv *env, jobject thiz) {
    MCOptimizer::VulkanRenderer::getInstance().swapBuffers();
}

JNIEXPORT void JNICALL
Java_com_mcoptimizer_jni_NativeBridge_setFrameRate(JNIEnv *env, jobject thiz, jint fps) {
    MCOptimizer::FramePacer::getInstance().setTargetFPS(fps);
}

JNIEXPORT jlong JNICALL
Java_com_mcoptimizer_jni_NativeBridge_getFrameTime(JNIEnv *env, jobject thiz) {
    return MCOptimizer::FramePacer::getInstance().getLastFrameTime();
}

JNIEXPORT void JNICALL
Java_com_mcoptimizer_jni_NativeBridge_enableFramePacing(JNIEnv *env, jobject thiz, 
                                                         jboolean enabled) {
    MCOptimizer::FramePacer::getInstance().setEnabled(enabled);
}

JNIEXPORT jlong JNICALL
Java_com_mcoptimizer_jni_NativeBridge_allocateMemoryPool(JNIEnv *env, jobject thiz, 
                                                          jlong size) {
    return reinterpret_cast<jlong>(MCOptimizer::MemoryPool::allocate(size));
}

JNIEXPORT void JNICALL
Java_com_mcoptimizer_jni_NativeBridge_freeMemoryPool(JNIEnv *env, jobject thiz, 
                                                      jlong pointer) {
    MCOptimizer::MemoryPool::free(reinterpret_cast<void*>(pointer));
}

JNIEXPORT void JNICALL
Java_com_mcoptimizer_optimizer_RenderOptimizer_nativeApplyOptimizations(JNIEnv *env, 
                                                                         jobject thiz) {
    MCOptimizer::Logger::info(LOG_TAG, "Applying native optimizations...");
    MCOptimizer::FramePacer::getInstance().optimize();
}

JNIEXPORT void JNICALL
Java_com_mcoptimizer_optimizer_MemoryManager_nativeClearMemoryPool(JNIEnv *env, 
                                                                    jobject thiz) {
    MCOptimizer::MemoryPool::clear();
}

JNIEXPORT void JNICALL
Java_com_mcoptimizer_optimizer_MemoryManager_nativeOptimizeMemoryPool(JNIEnv *env, 
                                                                       jobject thiz) {
    MCOptimizer::MemoryPool::optimize();
}

} // extern "C"
