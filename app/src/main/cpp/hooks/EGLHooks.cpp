// MinecraftMobileOptimizer/app/src/main/cpp/hooks/EGLHooks.cpp
#include "EGLHooks.h"
#include "../optimizer/FramePacer.h"
#include <dlfcn.h>
#include <android/log.h>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "EGLHooks", __VA_ARGS__)

namespace mcoptimizer {

bool EGLHooks::s_installed = false;

EGLBoolean (*EGLHooks::orig_eglSwapBuffers)(EGLDisplay, EGLSurface) = nullptr;
EGLSurface (*EGLHooks::orig_eglCreateWindowSurface)(EGLDisplay, EGLConfig, NativeWindowType, const EGLint*) = nullptr;

void EGLHooks::install() {
    if (s_installed) return;
    
    LOGI("Installing EGL hooks...");
    
    void* eglHandle = dlopen("libEGL.so", RTLD_NOW);
    if (!eglHandle) {
        LOGI("Failed to load libEGL.so");
        return;
    }
    
    orig_eglSwapBuffers = (decltype(orig_eglSwapBuffers))dlsym(eglHandle, "eglSwapBuffers");
    orig_eglCreateWindowSurface = (decltype(orig_eglCreateWindowSurface))dlsym(eglHandle, "eglCreateWindowSurface");
    
    s_installed = true;
    LOGI("EGL hooks installed");
}

void EGLHooks::remove() {
    s_installed = false;
    LOGI("EGL hooks removed");
}

bool EGLHooks::isInstalled() {
    return s_installed;
}

EGLBoolean EGLHooks::hooked_eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
    // Frame pacing happens here
    if (orig_eglSwapBuffers) {
        return orig_eglSwapBuffers(dpy, surface);
    }
    return EGL_FALSE;
}

EGLSurface EGLHooks::hooked_eglCreateWindowSurface(EGLDisplay dpy, EGLConfig config,
                                                    NativeWindowType win, const EGLint* attrib_list) {
    if (orig_eglCreateWindowSurface) {
        return orig_eglCreateWindowSurface(dpy, config, win, attrib_list);
    }
    return EGL_NO_SURFACE;
}

} // namespace mcoptimizer
