// MinecraftMobileOptimizer/app/src/main/java/com/mcoptimizer/optimizer/MemoryManager.java
package com.mcoptimizer.optimizer;

import android.content.Context;
import com.mcoptimizer.jni.NativeBridge;

public class MemoryManager {
    
    private final Context context;
    
    public MemoryManager(Context context) {
        this.context = context;
    }
    
    public void performGC() {
        System.gc();
        NativeBridge.optimizeMemory();
    }
    
    public void clearCache() {
        context.getCacheDir().delete();
        if (context.getExternalCacheDir() != null) {
            context.getExternalCacheDir().delete();
        }
    }
    
    public void trimMemory() {
        performGC();
        clearCache();
        NativeBridge.optimizeMemory();
    }
}
