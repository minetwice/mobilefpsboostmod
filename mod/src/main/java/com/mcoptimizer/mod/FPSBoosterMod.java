// MinecraftMobileOptimizer/mod/src/main/java/com/mcoptimizer/mod/FPSBoosterMod.java
package com.mcoptimizer.mod;

import net.fabricmc.api.ModInitializer;
import net.fabricmc.fabric.api.client.event.lifecycle.v1.ClientTickEvents;
import net.minecraft.client.MinecraftClient;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class FPSBoosterMod implements ModInitializer {
    public static final String MOD_ID = "mcoptimizer";
    public static final Logger LOGGER = LoggerFactory.getLogger(MOD_ID);
    
    private static final FPSBoosterMod INSTANCE = new FPSBoosterMod();
    private PerformanceOptimizer optimizer;
    private int tickCounter = 0;
    
    public static FPSBoosterMod getInstance() {
        return INSTANCE;
    }
    
    @Override
    public void onInitialize() {
        LOGGER.info("MC Optimizer v1.0.0 for Minecraft 1.21.11 initializing...");
        
        optimizer = new PerformanceOptimizer();
        
        ClientTickEvents.END_CLIENT_TICK.register(client -> {
            tickCounter++;
            if (tickCounter % 20 == 0) {
                optimizer.optimize(client);
            }
        });
        
        LOGGER.info("MC Optimizer initialized! Java 21 | MC 1.21.11");
    }
    
    public PerformanceOptimizer getOptimizer() {
        return optimizer;
    }
}
