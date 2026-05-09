// MinecraftMobileOptimizer/app/src/main/cpp/core/Engine.h
#pragma once

#include <memory>
#include <atomic>

namespace mcoptimizer {

class VulkanRenderer;
class FramePacer;
class MemoryPool;
class TextureCache;

class Engine {
public:
    Engine();
    ~Engine();
    
    // Lifecycle
    bool initialize(int targetFps);
    void shutdown();
    
    // Frame management
    void beginFrame();
    void endFrame();
    
    // Render control
    void setRenderScale(float scale);
    float getRenderScale() const;
    
    // Performance
    int getCurrentFps() const;
    float getFrameTimeMs() const;
    void setTargetFps(int fps);
    
    // Memory
    void optimizeMemory();
    size_t getUsedMemory() const;
    size_t getFreeMemory() const;
    
    // State
    bool isInitialized() const { return m_initialized; }
    
private:
    std::unique_ptr<VulkanRenderer> m_renderer;
    std::unique_ptr<FramePacer> m_framePacer;
    std::unique_ptr<MemoryPool> m_memoryPool;
    std::unique_ptr<TextureCache> m_textureCache;
    
    std::atomic<bool> m_initialized{false};
    std::atomic<float> m_renderScale{1.0f};
};

} // namespace mcoptimizer
