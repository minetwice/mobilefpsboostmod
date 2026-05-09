// MinecraftMobileOptimizer/app/src/main/java/com/mcoptimizer/launcher/MainActivity.java
package com.mcoptimizer.launcher;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.widget.Button;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;
import androidx.appcompat.app.AppCompatActivity;
import com.mcoptimizer.R;
import com.mcoptimizer.jni.NativeBridge;

public class MainActivity extends AppCompatActivity {
    
    private TextView fpsText, fpsDisplay;
    private SeekBar targetFpsSeekBar, renderScaleSeekBar;
    private int targetFps = 60;
    private float renderScale = 1.0f;
    private final Handler handler = new Handler(Looper.getMainLooper());
    
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        initViews();
        setupListeners();
        NativeBridge.initOptimizer(targetFps);
        startFpsMonitoring();
    }
    
    private void initViews() {
        fpsText = findViewById(R.id.fpsText);
        targetFpsSeekBar = findViewById(R.id.targetFpsSeekBar);
        renderScaleSeekBar = findViewById(R.id.renderScaleSeekBar);
        fpsDisplay = findViewById(R.id.fpsDisplay);
        
        findViewById(R.id.launchButton).setOnClickListener(v -> launchMinecraft());
        findViewById(R.id.optimizeButton).setOnClickListener(v -> optimizeNow());
    }
    
    private void setupListeners() {
        targetFpsSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                targetFps = progress + 30;
                fpsText.setText("Target FPS: " + targetFps);
            }
            @Override public void onStartTrackingTouch(SeekBar seekBar) {}
            @Override public void onStopTrackingTouch(SeekBar seekBar) {
                NativeBridge.initOptimizer(targetFps);
            }
        });
        
        renderScaleSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                renderScale = 0.5f + (progress / 100f) * 0.5f;
                NativeBridge.setRenderScale(renderScale);
            }
            @Override public void onStartTrackingTouch(SeekBar seekBar) {}
            @Override public void onStopTrackingTouch(SeekBar seekBar) {}
        });
    }
    
    private void launchMinecraft() {
        Intent intent = new Intent(this, LauncherActivity.class);
        intent.putExtra("TARGET_FPS", targetFps);
        intent.putExtra("RENDER_SCALE", renderScale);
        startActivity(intent);
    }
    
    private void optimizeNow() {
        NativeBridge.optimizeMemory();
        Toast.makeText(this, "Memory Optimized!", Toast.LENGTH_SHORT).show();
    }
    
    private void startFpsMonitoring() {
        handler.postDelayed(new Runnable() {
            @Override public void run() {
                int fps = NativeBridge.getCurrentFps();
                fpsDisplay.setText("Current FPS: " + fps);
                handler.postDelayed(this, 1000);
            }
        }, 1000);
    }
    
    @Override protected void onDestroy() {
        super.onDestroy();
        NativeBridge.shutdown();
    }
}
