#ifndef GL_INTERCEPTOR_H
#define GL_INTERCEPTOR_H

#include <GLES3/gl3.h>
#include <string>

namespace MCOptimizer {

class GLInterceptor {
public:
    static GLInterceptor& getInstance();
    
    void initialize();
    void interceptGLCalls();
    
    // Intercepted OpenGL functions
    void glDrawArrays(GLenum mode, GLint first, GLsizei count);
    void glDrawElements(GLenum mode, GLsizei count, GLenum type, const void* indices);
    void glTexImage2D(GLenum target, GLint level, GLint internalformat, 
                      GLsizei width, GLsizei height, GLint border, 
                      GLenum format, GLenum type, const void* pixels);
    
    // Performance tracking
    int getDrawCallCount() const { return m_drawCallCount; }
    int getTextureCount() const { return m_textureCount; }
    void resetCounters();
    
private:
    GLInterceptor() = default;
    ~GLInterceptor() = default;
    GLInterceptor(const GLInterceptor&) = delete;
    GLInterceptor& operator=(const GLInterceptor&) = delete;
    
    int m_drawCallCount = 0;
    int m_textureCount = 0;
    bool m_initialized = false;
};

} // namespace MCOptimizer

#endif // GL_INTERCEPTOR_H
