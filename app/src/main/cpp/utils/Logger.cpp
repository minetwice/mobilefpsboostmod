// MinecraftMobileOptimizer/app/src/main/cpp/utils/Logger.cpp
#include "Logger.h"

void Logger::init() { MC_LOGI("Logger init - MC 1.21.11"); }
void Logger::setLogLevel(int level) { MC_LOGI("Log level: %d", level); }
void Logger::logPerformanceStats() { MC_LOGI("Performance stats"); }
