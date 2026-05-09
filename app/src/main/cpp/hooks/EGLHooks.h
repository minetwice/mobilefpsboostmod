// MinecraftMobileOptimizer/app/src/main/cpp/hooks/EGLHooks.h
#pragma once

#include <EGL/egl.h>

namespace mcoptimizer {

class EGLHooks {
public:
    static void install();
    static void remove();
    static bool isInstalled();
    
    // Hooked EGL functions
    static EGLBoolean hooked_eglSwapBuffers(EGLDisplay dpy, EGLSurface surface);
    static EGLSurface hooked_eglCreateWindowSurface(EGLDisplay dpy, EGLConfig config,
                                                     NativeWindowType win, const EGLint* attrib_list);
    
private:
    static bool s_installed;
    
    static EGLBoolean (*orig_eglSwapBuffers)(EGLDisplay, EGLSurface);
    static EGLSurface (*orig_eglCreateWindowSurface)(EGLDisplay, EGLConfig, NativeWindowType, const EGLint*);
};

} // namespace mcoptimizer
