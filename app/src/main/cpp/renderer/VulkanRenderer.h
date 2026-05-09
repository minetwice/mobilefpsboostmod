#ifndef VULKAN_RENDERER_H
#define VULKAN_RENDERER_H

#include <vulkan/vulkan.h>
#include <string>
#include <vector>

namespace MCOptimizer {

class VulkanRenderer {
public:
    static VulkanRenderer& getInstance();
    
    bool initialize();
    void destroy();
    
    void setResolution(int width, int height);
    void swapBuffers();
    
    bool isInitialized() const { return m_initialized; }
    
private:
    VulkanRenderer() = default;
    ~VulkanRenderer() = default;
    VulkanRenderer(const VulkanRenderer&) = delete;
    VulkanRenderer& operator=(const VulkanRenderer&) = delete;
    
    bool createInstance();
    bool createDevice();
    bool createSwapchain();
    void cleanupSwapchain();
    
    VkInstance m_instance = VK_NULL_HANDLE;
    VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
    VkDevice m_device = VK_NULL_HANDLE;
    VkSurfaceKHR m_surface = VK_NULL_HANDLE;
    VkSwapchainKHR m_swapchain = VK_NULL_HANDLE;
    
    int m_width = 0;
    int m_height = 0;
    bool m_initialized = false;
};

} // namespace MCOptimizer

#endif // VULKAN_RENDERER_H
