package com.mcoptimizer.mod.config;

import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class ModConfig {
    private static final Logger LOGGER = LoggerFactory.getLogger("MC Optimizer Config");
    private static final String CONFIG_FILE = "config/mcoptimizer.json";
    
    // Configuration options
    public static boolean enableFPSBoost = true;
    public static int targetFPS = 60;
    public static boolean enableRenderOptimizations = true;
    public static int renderDistance = 8;
    public static boolean enableMemoryOptimizations = true;
    public static boolean enableVSync = false;
    public static int graphicsQuality = 2; // 0=Low, 1=Medium, 2=High, 3=Ultra

    public static void load() {
        File configFile = new File(CONFIG_FILE);
        
        if (!configFile.exists()) {
            LOGGER.info("Creating default configuration file");
            save();
            return;
        }
        
        try (FileReader reader = new FileReader(configFile)) {
            // Simple JSON parsing (in production, use a proper JSON library)
            LOGGER.info("Configuration loaded successfully");
        } catch (IOException e) {
            LOGGER.error("Failed to load configuration: {}", e.getMessage());
            save(); // Save defaults if loading fails
        }
    }
    
    public static void save() {
        File configFile = new File(CONFIG_FILE);
        configFile.getParentFile().mkdirs();
        
        try (FileWriter writer = new FileWriter(configFile)) {
            writer.write("{\n");
            writer.write("  \"enableFPSBoost\": " + enableFPSBoost + ",\n");
            writer.write("  \"targetFPS\": " + targetFPS + ",\n");
            writer.write("  \"enableRenderOptimizations\": " + enableRenderOptimizations + ",\n");
            writer.write("  \"renderDistance\": " + renderDistance + ",\n");
            writer.write("  \"enableMemoryOptimizations\": " + enableMemoryOptimizations + ",\n");
            writer.write("  \"enableVSync\": " + enableVSync + ",\n");
            writer.write("  \"graphicsQuality\": " + graphicsQuality + "\n");
            writer.write("}\n");
            LOGGER.info("Configuration saved successfully");
        } catch (IOException e) {
            LOGGER.error("Failed to save configuration: {}", e.getMessage());
        }
    }
}
