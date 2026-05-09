package com.mcoptimizer.mod;

import net.fabricmc.api.ModInitializer;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class FPSBoosterMod implements ModInitializer {
    public static final String MOD_ID = "mcoptimizer";
    public static final Logger LOGGER = LoggerFactory.getLogger(MOD_ID);

    @Override
    public void onInitialize() {
        LOGGER.info("MC Optimizer - FPS Booster initializing...");
        
        // Initialize mod configuration
        ModConfig.load();
        
        // Register mixins are handled automatically via fabric.mod.json
        
        LOGGER.info("MC Optimizer initialized successfully!");
        LOGGER.info("FPS optimizations enabled");
    }
}
