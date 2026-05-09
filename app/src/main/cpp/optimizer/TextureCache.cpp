// MinecraftMobileOptimizer/app/src/main/cpp/optimizer/TextureCache.cpp
#include "TextureCache.h"
#include <chrono>
#include <GLES3/gl3.h>
#include <android/log.h>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "TextureCache", __VA_ARGS__)

namespace mcoptimizer {

TextureCache::TextureCache() : m_totalMemory(0) {}
TextureCache::~TextureCache() {
    clearAll();
}

void TextureCache::cache(uint32_t glId, uint32_t width, uint32_t height, uint32_t format) {
    std::lock_guard<std::mutex> lock(m_mutex);
    
    size_t bpp = (format == GL_RGBA) ? 4 : 3;
    size_t memorySize = width * height * bpp;
    
    CachedTexture tex{glId, width, height, format, memorySize, getTimestamp(), 1};
    m_textures[glId] = tex;
    m_totalMemory += memorySize;
    
    LOGI("Cached texture %u: %ux%u, %.2f MB", glId, width, height, 
         memorySize / (1024.0f * 1024.0f));
}

void TextureCache::markUsed(uint32_t glId) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_textures.find(glId);
    if (it != m_textures.end()) {
        it->second.lastUsed = getTimestamp();
        it->second.useCount++;
    }
}

void TextureCache::remove(uint32_t glId) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_textures.find(glId);
    if (it != m_textures.end()) {
        m_totalMemory -= it->second.memorySize;
        m_textures.erase(it);
    }
}

void TextureCache::clearUnused() {
    std::lock_guard<std::mutex> lock(m_mutex);
    
    uint64_t now = getTimestamp();
    uint64_t threshold = 30000; // 30 seconds
    
    std::vector<uint32_t> toRemove;
    for (const auto& [id, tex] : m_textures) {
        if (now - tex.lastUsed > threshold && tex.useCount < 5) {
            toRemove.push_back(id);
        }
    }
    
    for (uint32_t id : toRemove) {
        m_totalMemory -= m_textures[id].memorySize;
        m_textures.erase(id);
    }
    
    LOGI("Cleared %zu unused textures, freed %.2f MB", 
         toRemove.size(), m_totalMemory / (1024.0f * 1024.0f));
}

void TextureCache::clearAll() {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_textures.clear();
    m_totalMemory = 0;
    LOGI("All textures cleared");
}

size_t TextureCache::getTotalMemory() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_totalMemory;
}

size_t TextureCache::getTextureCount() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_textures.size();
}

uint64_t TextureCache::getTimestamp() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now().time_since_epoch()).count();
}

} // namespace mcoptimizer
