package com.mcoptimizer.optimizer

import android.util.Log

object MemoryManager {
    private const val TAG = "MemoryManager"
    private const val MAX_HEAP_SIZE_MB = 512L

    fun clearCache() {
        Log.d(TAG, "Clearing memory cache")
        System.gc()
        nativeClearMemoryPool()
    }

    fun getAvailableMemory(): Long {
        val runtime = Runtime.getRuntime()
        return runtime.maxMemory() - runtime.totalMemory() + runtime.freeMemory()
    }

    fun getUsedMemory(): Long {
        val runtime = Runtime.getRuntime()
        return runtime.totalMemory() - runtime.freeMemory()
    }

    fun optimizeMemoryAllocation() {
        Log.d(TAG, "Optimizing memory allocation")
        nativeOptimizeMemoryPool()
    }

    fun setMaxHeapSize(sizeMb: Long) {
        Log.d(TAG, "Setting max heap size to: ${sizeMb}MB")
    }

    private external fun nativeClearMemoryPool()
    private external fun nativeOptimizeMemoryPool()
}
