package com.mcoptimizer.jni

import android.util.Log

object NativeBridge {
    private const val TAG = "NativeBridge"

    init {
        try {
            System.loadLibrary("mcoptimizer")
            Log.d(TAG, "Native library loaded successfully")
        } catch (e: UnsatisfiedLinkError) {
            Log.e(TAG, "Failed to load native library: ${e.message}")
        }
    }

    // Renderer native methods
    external fun initRenderer(): Boolean
    external fun destroyRenderer()
    external fun setResolution(width: Int, height: Int)
    external fun swapBuffers()

    // Frame pacing
    external fun setFrameRate(fps: Int)
    external fun getFrameTime(): Long
    external fun enableFramePacing(enabled: Boolean)

    // Memory management
    external fun allocateMemoryPool(size: Long): Long
    external fun freeMemoryPool(pointer: Long)
    external fun getMemoryStats(): MemoryStats

    // Optimization
    external fun applyOptimizations(level: Int)
    external fun resetOptimizations()

    data class MemoryStats(
        val allocatedBytes: Long,
        val freeBytes: Long,
        val peakUsageBytes: Long
    )
}
