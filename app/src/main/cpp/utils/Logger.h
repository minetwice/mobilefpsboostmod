// MinecraftMobileOptimizer/app/src/main/cpp/utils/Logger.h
#pragma once
#include <android/log.h>

#define MC_LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, "MCOptimizer", __VA_ARGS__)
#define MC_LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "MCOptimizer", __VA_ARGS__)
#define MC_LOGI(...) __android_log_print(ANDROID_LOG_INFO, "MCOptimizer", __VA_ARGS__)
#define MC_LOGW(...) __android_log_print(ANDROID_LOG_WARN, "MCOptimizer", __VA_ARGS__)
#define MC_LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "MCOptimizer", __VA_ARGS__)

class Logger {
public:
    static void init();
    static void setLogLevel(int level);
    static void logPerformanceStats();
};
