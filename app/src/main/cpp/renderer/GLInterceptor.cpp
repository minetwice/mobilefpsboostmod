#include "GLInterceptor.h"
#include "utils/Logger.h"

namespace MCOptimizer {

GLInterceptor& GLInterceptor::getInstance() {
    static GLInterceptor instance;
    return instance;
}

void GLInterceptor::initialize() {
    if (m_initialized) return;
    
    Logger::info("GLInterceptor", "Initializing OpenGL interceptor...");
    m_initialized = true;
}

void GLInterceptor::interceptGLCalls() {
    // Implementation for intercepting OpenGL calls
    Logger::debug("GLInterceptor", "Intercepting GL calls");
}

void GLInterceptor::glDrawArrays(GLenum mode, GLint first, GLsizei count) {
    m_drawCallCount++;
    ::glDrawArrays(mode, first, count);
}

void GLInterceptor::glDrawElements(GLenum mode, GLsizei count, GLenum type, const void* indices) {
    m_drawCallCount++;
    ::glDrawElements(mode, count, type, indices);
}

void GLInterceptor::glTexImage2D(GLenum target, GLint level, GLint internalformat,
                                  GLsizei width, GLsizei height, GLint border,
                                  GLenum format, GLenum type, const void* pixels) {
    m_textureCount++;
    ::glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
}

void GLInterceptor::resetCounters() {
    m_drawCallCount = 0;
    m_textureCount = 0;
    Logger::debug("GLInterceptor", "Counters reset");
}

} // namespace MCOptimizer
