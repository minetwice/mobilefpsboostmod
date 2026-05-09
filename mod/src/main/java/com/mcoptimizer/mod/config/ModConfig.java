// MinecraftMobileOptimizer/mod/src/main/java/com/mcoptimizer/mod/config/ModConfig.java
package com.mcoptimizer.mod.config;

public class ModConfig {
    public boolean dynamicResolution = true;
    public boolean aggressiveOptimization = true;
    public int minFpsThreshold = 30;
    public int targetFps = 60;
    public float minRenderScale = 0.5f;
    public boolean enableCulling = true;
    public boolean enableBatching = true;
    public boolean enableLOD = true;
    
    public static ModConfig DEFAULT = new ModConfig();
}
