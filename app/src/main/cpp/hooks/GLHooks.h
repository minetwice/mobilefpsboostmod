// MinecraftMobileOptimizer/app/src/main/cpp/hooks/GLHooks.h
#pragma once

#include <GLES3/gl3.h>

namespace mcoptimizer {

class GLHooks {
public:
    static void install();
    static void remove();
    static bool isInstalled();
    
    // Hooked functions
    static void hooked_glDrawArrays(GLenum mode, GLint first, GLsizei count);
    static void hooked_glDrawElements(GLenum mode, GLsizei count, GLenum type, const void* indices);
    static void hooked_glBindTexture(GLenum target, GLuint texture);
    static void hooked_glUseProgram(GLuint program);
    static void hooked_glTexImage2D(GLenum target, GLint level, GLint internalformat,
                                    GLsizei width, GLsizei height, GLint border,
                                    GLenum format, GLenum type, const void* pixels);
    
private:
    static bool s_installed;
    
    // Original function pointers
    static void (*orig_glDrawArrays)(GLenum, GLint, GLsizei);
    static void (*orig_glDrawElements)(GLenum, GLsizei, GLenum, const void*);
    static void (*orig_glBindTexture)(GLenum, GLuint);
    static void (*orig_glUseProgram)(GLuint);
    static void (*orig_glTexImage2D)(GLenum, GLint, GLint, GLsizei, GLsizei, GLint,
                                     GLenum, GLenum, const void*);
};

} // namespace mcoptimizer
