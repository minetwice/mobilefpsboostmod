// MinecraftMobileOptimizer/app/src/main/cpp/hooks/GLHooks.cpp
#include "GLHooks.h"
#include "../renderer/GLInterceptor.h"
#include "../utils/Logger.h"
#include <dlfcn.h>
#include <android/log.h>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "GLHooks", __VA_ARGS__)

namespace mcoptimizer {

bool GLHooks::s_installed = false;

// Original function pointers
void (*GLHooks::orig_glDrawArrays)(GLenum, GLint, GLsizei) = nullptr;
void (*GLHooks::orig_glDrawElements)(GLenum, GLsizei, GLenum, const void*) = nullptr;
void (*GLHooks::orig_glBindTexture)(GLenum, GLuint) = nullptr;
void (*GLHooks::orig_glUseProgram)(GLuint) = nullptr;
void (*GLHooks::orig_glTexImage2D)(GLenum, GLint, GLint, GLsizei, GLsizei, GLint,
                                    GLenum, GLenum, const void*) = nullptr;

void GLHooks::install() {
    if (s_installed) return;
    
    LOGI("Installing OpenGL hooks...");
    
    // Get original functions from GLESv3
    void* glesHandle = dlopen("libGLESv3.so", RTLD_NOW);
    if (!glesHandle) {
        LOG_ERROR("Failed to load libGLESv3.so");
        return;
    }
    
    orig_glDrawArrays = (decltype(orig_glDrawArrays))dlsym(glesHandle, "glDrawArrays");
    orig_glDrawElements = (decltype(orig_glDrawElements))dlsym(glesHandle, "glDrawElements");
    orig_glBindTexture = (decltype(orig_glBindTexture))dlsym(glesHandle, "glBindTexture");
    orig_glUseProgram = (decltype(orig_glUseProgram))dlsym(glesHandle, "glUseProgram");
    orig_glTexImage2D = (decltype(orig_glTexImage2D))dlsym(glesHandle, "glTexImage2D");
    
    // Initialize interceptor
    GLInterceptor::initialize();
    
    s_installed = true;
    LOGI("OpenGL hooks installed successfully");
}

void GLHooks::remove() {
    if (!s_installed) return;
    
    LOGI("Removing OpenGL hooks...");
    GLInterceptor::shutdown();
    s_installed = false;
}

bool GLHooks::isInstalled() {
    return s_installed;
}

void GLHooks::hooked_glDrawArrays(GLenum mode, GLint first, GLsizei count) {
    GLInterceptor::onDrawArrays(mode, first, count);
    if (orig_glDrawArrays) {
        orig_glDrawArrays(mode, first, count);
    }
}

void GLHooks::hooked_glDrawElements(GLenum mode, GLsizei count, GLenum type, const void* indices) {
    GLInterceptor::onDrawElements(mode, count, type, indices);
    if (orig_glDrawElements) {
        orig_glDrawElements(mode, count, type, indices);
    }
}

void GLHooks::hooked_glBindTexture(GLenum target, GLuint texture) {
    GLInterceptor::onBindTexture(texture);
    if (orig_glBindTexture) {
        orig_glBindTexture(target, texture);
    }
}

void GLHooks::hooked_glUseProgram(GLuint program) {
    GLInterceptor::onUseProgram(program);
    if (orig_glUseProgram) {
        orig_glUseProgram(program);
    }
}

void GLHooks::hooked_glTexImage2D(GLenum target, GLint level, GLint internalformat,
                                   GLsizei width, GLsizei height, GLint border,
                                   GLenum format, GLenum type, const void* pixels) {
    if (orig_glTexImage2D) {
        orig_glTexImage2D(target, level, internalformat, width, height, border,
                         format, type, pixels);
    }
}

} // namespace mcoptimizer
