// MinecraftMobileOptimizer/app/src/main/java/com/mcoptimizer/optimizer/PerformanceMonitor.java
package com.mcoptimizer.optimizer;

import android.app.ActivityManager;
import android.content.Context;
import android.os.Process;
import com.mcoptimizer.jni.NativeBridge;

public class PerformanceMonitor {
    
    private final ActivityManager activityManager;
    
    public PerformanceMonitor(Context context) {
        this.activityManager = (ActivityManager) context.getSystemService(Context.ACTIVITY_SERVICE);
    }
    
    public record PerformanceStats(int fps, long memoryUsedMB, long memoryTotalMB, 
                                    float cpuUsage, float temperature) {}
    
    public PerformanceStats getCurrentStats() {
        ActivityManager.MemoryInfo memInfo = new ActivityManager.MemoryInfo();
        activityManager.getMemoryInfo(memInfo);
        
        Runtime runtime = Runtime.getRuntime();
        long usedMem = (runtime.totalMemory() - runtime.freeMemory()) / (1024 * 1024);
        long totalMem = runtime.maxMemory() / (1024 * 1024);
        
        return new PerformanceStats(
            NativeBridge.getCurrentFps(),
            usedMem,
            totalMem,
            getCpuUsage(),
            getDeviceTemperature()
        );
    }
    
    private float getCpuUsage() {
        try {
            int pid = Process.myPid();
            Process process = Runtime.getRuntime().exec("cat /proc/" + pid + "/stat");
            process.waitFor();
            return 0f;
        } catch (Exception e) {
            return 0f;
        }
    }
    
    private float getDeviceTemperature() {
        try {
            Process process = Runtime.getRuntime().exec("cat /sys/class/thermal/thermal_zone0/temp");
            process.waitFor();
            return 0f;
        } catch (Exception e) {
            return 0f;
        }
    }
    
    public boolean shouldReduceQuality(PerformanceStats stats) {
        return stats.fps < 30 || stats.temperature > 45f || 
               stats.memoryUsedMB > stats.memoryTotalMB * 0.85;
    }
    
    public record OptimizationSettings(float renderScale, int particleLimit, float entityDistance) {}
    
    public OptimizationSettings getRecommendedSettings(PerformanceStats stats) {
        return switch (stats.fps / 10) {
            case 0, 1 -> new OptimizationSettings(0.5f, 50, 50f);
            case 2, 3 -> new OptimizationSettings(0.75f, 100, 75f);
            default -> new OptimizationSettings(1.0f, 200, 128f);
        };
    }
}
