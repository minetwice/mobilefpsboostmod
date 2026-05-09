// MinecraftMobileOptimizer/app/src/main/cpp/core/Engine.cpp
#include "Engine.h"
#include "../renderer/VulkanRenderer.h"
#include "../optimizer/FramePacer.h"
#include "../optimizer/MemoryPool.h"
#include "../optimizer/TextureCache.h"
#include "../utils/Logger.h"

namespace mcoptimizer {

Engine::Engine() = default;
Engine::~Engine() {
    shutdown();
}

bool Engine::initialize(int targetFps) {
    LOG_INFO("Initializing engine with target FPS: %d", targetFps);
    
    m_framePacer = std::make_unique<FramePacer>(targetFps);
    m_memoryPool = std::make_unique<MemoryPool>(512 * 1024 * 1024); // 512MB
    m_renderer = std::make_unique<VulkanRenderer>();
    m_textureCache = std::make_unique<TextureCache>();
    
    if (!m_renderer->initialize()) {
        LOG_ERROR("Renderer initialization failed");
        return false;
    }
    
    m_initialized = true;
    LOG_INFO("Engine initialized successfully");
    return true;
}

void Engine::shutdown() {
    LOG_INFO("Shutting down engine...");
    m_textureCache.reset();
    m_renderer.reset();
    m_framePacer.reset();
    m_memoryPool.reset();
    m_initialized = false;
}

void Engine::beginFrame() {
    if (m_framePacer) {
        m_framePacer->beginFrame();
    }
}

void Engine::endFrame() {
    if (m_framePacer) {
        m_framePacer->endFrame();
    }
}

void Engine::setRenderScale(float scale) {
    m_renderScale = scale;
    if (m_renderer) {
        m_renderer->setRenderScale(scale);
    }
}

float Engine::getRenderScale() const {
    return m_renderScale.load();
}

int Engine::getCurrentFps() const {
    return m_framePacer ? m_framePacer->getCurrentFps() : 0;
}

float Engine::getFrameTimeMs() const {
    return m_framePacer ? m_framePacer->getFrameTimeMs() : 0.0f;
}

void Engine::setTargetFps(int fps) {
    if (m_framePacer) {
        m_framePacer->setTargetFps(fps);
    }
}

void Engine::optimizeMemory() {
    if (m_memoryPool) {
        m_memoryPool->defragment();
        m_memoryPool->releaseUnused();
    }
    if (m_textureCache) {
        m_textureCache->clearUnused();
    }
}

size_t Engine::getUsedMemory() const {
    return m_memoryPool ? m_memoryPool->getUsedMemory() : 0;
}

size_t Engine::getFreeMemory() const {
    return m_memoryPool ? m_memoryPool->getFreeMemory() : 0;
}

} // namespace mcoptimizer
