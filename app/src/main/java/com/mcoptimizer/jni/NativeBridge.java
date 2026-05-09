// MinecraftMobileOptimizer/app/src/main/java/com/mcoptimizer/jni/NativeBridge.java
package com.mcoptimizer.jni;

public class NativeBridge {
    
    static {
        System.loadLibrary("mcoptimizer");
    }
    
    public static native void initOptimizer(int targetFps);
    public static native void beginFrame();
    public static native void endFrame();
    public static native void optimizeMemory();
    public static native void setRenderScale(float scale);
    public static native int getCurrentFps();
    public static native void shutdown();
}
