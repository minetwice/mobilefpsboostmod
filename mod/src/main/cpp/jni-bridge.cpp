// MinecraftMobileOptimizer/mod/src/main/cpp/jni-bridge.cpp
// JNI Bridge for Minecraft Mod to communicate with native optimizer

#include <jni.h>
#include <android/log.h>
#include "optimizer-native.h"

#define LOG_TAG "MCOptimizerMod"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

extern "C" {

JNIEXPORT void JNICALL
Java_com_mcoptimizer_mod_NativeBridge_notifyFrameStart(JNIEnv* env, jclass clazz) {
    mcoptimizer::notifyFrameStart();
}

JNIEXPORT void JNICALL
Java_com_mcoptimizer_mod_NativeBridge_notifyFrameEnd(JNIEnv* env, jclass clazz) {
    mcoptimizer::notifyFrameEnd();
}

JNIEXPORT void JNICALL
Java_com_mcoptimizer_mod_NativeBridge_notifyRenderDistance(JNIEnv* env, jclass clazz, jint distance) {
    mcoptimizer::setRenderDistance(distance);
}

JNIEXPORT void JNICALL
Java_com_mcoptimizer_mod_NativeBridge_notifyEntityCount(JNIEnv* env, jclass clazz, jint count) {
    mcoptimizer::setEntityCount(count);
}

JNIEXPORT jint JNICALL
Java_com_mcoptimizer_mod_NativeBridge_getRecommendedRenderDistance(JNIEnv* env, jclass clazz) {
    return mcoptimizer::getRecommendedRenderDistance();
}

JNIEXPORT jboolean JNICALL
Java_com_mcoptimizer_mod_NativeBridge_shouldReduceQuality(JNIEnv* env, jclass clazz) {
    return mcoptimizer::shouldReduceQuality() ? JNI_TRUE : JNI_FALSE;
}

} // extern "C"
