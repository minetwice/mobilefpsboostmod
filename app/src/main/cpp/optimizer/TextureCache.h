// MinecraftMobileOptimizer/app/src/main/cpp/optimizer/TextureCache.h
#pragma once

#include <unordered_map>
#include <string>
#include <cstdint>
#include <mutex>

namespace mcoptimizer {

struct CachedTexture {
    uint32_t glId;
    uint32_t width;
    uint32_t height;
    uint32_t format;
    size_t memorySize;
    uint64_t lastUsed;
    uint32_t useCount;
};

class TextureCache {
public:
    TextureCache();
    ~TextureCache();
    
    void cache(uint32_t glId, uint32_t width, uint32_t height, uint32_t format);
    void markUsed(uint32_t glId);
    void remove(uint32_t glId);
    void clearUnused();
    void clearAll();
    
    size_t getTotalMemory() const;
    size_t getTextureCount() const;
    
private:
    std::unordered_map<uint32_t, CachedTexture> m_textures;
    mutable std::mutex m_mutex;
    size_t m_totalMemory;
    
    uint64_t getTimestamp();
};

} // namespace mcoptimizer
