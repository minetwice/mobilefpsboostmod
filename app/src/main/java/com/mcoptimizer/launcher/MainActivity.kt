package com.mcoptimizer.launcher

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import android.content.Intent
import android.widget.Button
import com.mcoptimizer.R

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val launchButton = findViewById<Button>(R.id.btn_launch_game)
        launchButton.setOnClickListener {
            startActivity(Intent(this, LauncherActivity::class.java))
        }

        val optimizeButton = findViewById<Button>(R.id.btn_optimize)
        optimizeButton.setOnClickListener {
            // Trigger optimization
            com.mcoptimizer.optimizer.RenderOptimizer.optimize(this)
        }
    }
}
