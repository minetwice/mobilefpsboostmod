// MinecraftMobileOptimizer/app/src/main/cpp/renderer/VulkanRenderer.h
#pragma once
#include <memory>

class VulkanRenderer {
public:
    VulkanRenderer();
    ~VulkanRenderer();
    bool initialize();
    void shutdown();
    void setRenderScale(float scale);
    float getRenderScale() const;
    void beginRenderPass();
    void endRenderPass();
    void interceptGLDrawArrays(int mode, int first, int count);
    void interceptGLDrawElements(int mode, int count, int type, const void* indices);
private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};
