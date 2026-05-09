// MinecraftMobileOptimizer/app/src/main/java/com/mcoptimizer/optimizer/RenderOptimizer.java
package com.mcoptimizer.optimizer;

import com.mcoptimizer.jni.NativeBridge;

public class RenderOptimizer {
    
    private float currentScale = 1.0f;
    
    public void applyDynamicResolution() {
        int fps = NativeBridge.getCurrentFps();
        currentScale = switch (fps / 10) {
            case 0, 1 -> 0.5f;
            case 2, 3 -> 0.65f;
            case 4 -> 0.8f;
            case 5 -> 0.9f;
            default -> 1.0f;
        };
        NativeBridge.setRenderScale(currentScale);
    }
    
    public void optimizeForLowMemory() {
        NativeBridge.optimizeMemory();
    }
    
    public float getCurrentRenderScale() { return currentScale; }
}
