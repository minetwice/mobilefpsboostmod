#include "Logger.h"
#include <cstdarg>
#include <cstdio>

namespace MCOptimizer {

LogLevel Logger::s_logLevel = LogLevel::DEBUG;

void Logger::init() {
    // Android logging is always available, no special initialization needed
}

void Logger::debug(const char* tag, const char* message) {
    if (s_logLevel <= LogLevel::DEBUG) {
        __android_log_print(ANDROID_LOG_DEBUG, tag, "%s", message);
    }
}

void Logger::info(const char* tag, const char* message) {
    if (s_logLevel <= LogLevel::INFO) {
        __android_log_print(ANDROID_LOG_INFO, tag, "%s", message);
    }
}

void Logger::warning(const char* tag, const char* message) {
    if (s_logLevel <= LogLevel::WARNING) {
        __android_log_print(ANDROID_LOG_WARN, tag, "%s", message);
    }
}

void Logger::error(const char* tag, const char* message) {
    if (s_logLevel <= LogLevel::ERROR) {
        __android_log_print(ANDROID_LOG_ERROR, tag, "%s", message);
    }
}

void Logger::debug(const char* tag, const char* format, ...) {
    if (s_logLevel <= LogLevel::DEBUG) {
        va_list args;
        va_start(args, format);
        log(LogLevel::DEBUG, tag, format, args);
        va_end(args);
    }
}

void Logger::info(const char* tag, const char* format, ...) {
    if (s_logLevel <= LogLevel::INFO) {
        va_list args;
        va_start(args, format);
        log(LogLevel::INFO, tag, format, args);
        va_end(args);
    }
}

void Logger::warning(const char* tag, const char* format, ...) {
    if (s_logLevel <= LogLevel::WARNING) {
        va_list args;
        va_start(args, format);
        log(LogLevel::WARNING, tag, format, args);
        va_end(args);
    }
}

void Logger::error(const char* tag, const char* format, ...) {
    if (s_logLevel <= LogLevel::ERROR) {
        va_list args;
        va_start(args, format);
        log(LogLevel::ERROR, tag, format, args);
        va_end(args);
    }
}

void Logger::log(LogLevel level, const char* tag, const char* message, va_list args) {
    android_LogPriority priority;
    switch (level) {
        case LogLevel::DEBUG:
            priority = ANDROID_LOG_DEBUG;
            break;
        case LogLevel::INFO:
            priority = ANDROID_LOG_INFO;
            break;
        case LogLevel::WARNING:
            priority = ANDROID_LOG_WARN;
            break;
        case LogLevel::ERROR:
            priority = ANDROID_LOG_ERROR;
            break;
        default:
            priority = ANDROID_LOG_UNKNOWN;
    }
    
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), message, args);
    __android_log_print(priority, tag, "%s", buffer);
}

} // namespace MCOptimizer
