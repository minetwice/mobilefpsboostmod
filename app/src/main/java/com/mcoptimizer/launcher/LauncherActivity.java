// MinecraftMobileOptimizer/app/src/main/java/com/mcoptimizer/launcher/LauncherActivity.java
package com.mcoptimizer.launcher;

import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.widget.TextView;
import androidx.appcompat.app.AppCompatActivity;
import com.mcoptimizer.R;
import com.mcoptimizer.jni.NativeBridge;

public class LauncherActivity extends AppCompatActivity {
    
    private TextView statusText;
    private final Handler handler = new Handler(Looper.getMainLooper());
    private volatile boolean running = true;
    
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_launcher);
        
        statusText = findViewById(R.id.statusText);
        
        int targetFps = getIntent().getIntExtra("TARGET_FPS", 60);
        float renderScale = getIntent().getFloatExtra("RENDER_SCALE", 1.0f);
        
        statusText.setText("MC 1.21.11 | Target: " + targetFps + " FPS | Scale: " + 
                          String.format("%.2f", renderScale));
        
        startGameLoop();
    }
    
    private void startGameLoop() {
        new Thread(() -> {
            while (running && !isDestroyed()) {
                NativeBridge.beginFrame();
                try { Thread.sleep(8); } catch (InterruptedException e) { break; }
                NativeBridge.endFrame();
            }
        }).start();
    }
    
    @Override protected void onDestroy() {
        running = false;
        super.onDestroy();
        NativeBridge.shutdown();
    }
}
