#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <android/log.h>

namespace MCOptimizer {

enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

class Logger {
public:
    static void init();
    
    static void debug(const char* tag, const char* message);
    static void info(const char* tag, const char* message);
    static void warning(const char* tag, const char* message);
    static void error(const char* tag, const char* message);
    
    // Printf-style logging
    static void debug(const char* tag, const char* format, ...);
    static void info(const char* tag, const char* format, ...);
    static void warning(const char* tag, const char* format, ...);
    static void error(const char* tag, const char* format, ...);
    
    static void setLogLevel(LogLevel level) { s_logLevel = level; }
    static LogLevel getLogLevel() { return s_logLevel; }
    
private:
    static LogLevel s_logLevel;
    static void log(LogLevel level, const char* tag, const char* message, va_list args);
};

} // namespace MCOptimizer

#endif // LOGGER_H
