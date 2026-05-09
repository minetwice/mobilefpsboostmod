// MinecraftMobileOptimizer/mod/src/main/java/com/mcoptimizer/mod/PerformanceOptimizer.java
package com.mcoptimizer.mod;

import net.minecraft.client.MinecraftClient;
import net.minecraft.client.option.GameOptions;
import net.minecraft.client.option.ParticlesMode;
import net.minecraft.client.option.CloudRenderMode;

public class PerformanceOptimizer {
    
    private boolean aggressiveMode = false;
    private int originalRenderDistance = 12;
    private ParticlesMode originalParticles = ParticlesMode.ALL;
    
    public void optimize(MinecraftClient client) {
        if (client == null || client.options == null) return;
        
        GameOptions options = client.options;
        int fps = client.getCurrentFps();
        
        if (fps < 20) {
            applyAggressiveOptimizations(options);
        } else if (fps < 40) {
            applyModerateOptimizations(options);
        } else if (aggressiveMode) {
            restoreSettings(options);
        }
    }
    
    private void applyAggressiveOptimizations(GameOptions options) {
        if (!aggressiveMode) {
            originalRenderDistance = options.getViewDistance().getValue();
            originalParticles = options.getParticles().getValue();
            aggressiveMode = true;
        }
        
        options.getViewDistance().setValue(Math.max(4, originalRenderDistance - 6));
        options.getParticles().setValue(ParticlesMode.MINIMAL);
        options.getEntityDistanceScaling().setValue(0.5);
        options.getCloudRenderMode().setValue(CloudRenderMode.OFF);
        options.getBiomeBlendRadius().setValue(0);
        
        FPSBoosterMod.LOGGER.info("Aggressive optimizations applied");
    }
    
    private void applyModerateOptimizations(GameOptions options) {
        options.getViewDistance().setValue(Math.max(6, originalRenderDistance - 3));
        options.getParticles().setValue(ParticlesMode.DECREASED);
        options.getEntityDistanceScaling().setValue(0.75);
    }
    
    private void restoreSettings(GameOptions options) {
        options.getViewDistance().setValue(originalRenderDistance);
        options.getParticles().setValue(originalParticles);
        options.getEntityDistanceScaling().setValue(1.0);
        aggressiveMode = false;
        FPSBoosterMod.LOGGER.info("Settings restored");
    }
    
    public boolean isAggressiveMode() {
        return aggressiveMode;
    }
}
