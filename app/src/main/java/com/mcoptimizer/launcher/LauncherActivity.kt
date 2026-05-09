package com.mcoptimizer.launcher

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import android.widget.TextView
import android.widget.Button
import android.util.Log
import com.mcoptimizer.R
import com.mcoptimizer.optimizer.RenderOptimizer
import com.mcoptimizer.optimizer.MemoryManager
import com.mcoptimizer.optimizer.PerformanceMonitor

class LauncherActivity : AppCompatActivity() {
    companion object {
        private const val TAG = "LauncherActivity"
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_launcher)

        val statusText = findViewById<TextView>(R.id.txt_status)
        val installButton = findViewById<Button>(R.id.btn_install_game)
        val launchButton = findViewById<Button>(R.id.btn_launch)

        // Initialize performance monitor
        PerformanceMonitor.startMonitoring()

        installButton.setOnClickListener {
            GameInstaller.installGame(this) { success ->
                runOnUiThread {
                    if (success) {
                        statusText.text = "Game installed successfully!"
                        launchButton.isEnabled = true
                    } else {
                        statusText.text = "Installation failed"
                    }
                }
            }
        }

        launchButton.setOnClickListener {
            Log.d(TAG, "Launching game with optimizations")
            RenderOptimizer.applyOptimizations()
            MemoryManager.clearCache()
            GameInstaller.launchGame()
        }
    }

    override fun onDestroy() {
        super.onDestroy()
        PerformanceMonitor.stopMonitoring()
    }
}
