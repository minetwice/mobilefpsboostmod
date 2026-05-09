#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include <cstddef>
#include <cstdint>
#include <vector>

namespace MCOptimizer {

struct MemoryBlock {
    void* data;
    size_t size;
    bool inUse;
};

class MemoryPool {
public:
    static MemoryPool& getInstance();
    
    static void* allocate(size_t size);
    static void free(void* ptr);
    static void clear();
    static void optimize();
    
    void initialize(size_t poolSize);
    void destroy();
    
    void* allocateBlock(size_t size);
    void freeBlock(void* ptr);
    
    size_t getTotalAllocated() const { return m_totalAllocated; }
    size_t getFreeMemory() const { return m_poolSize - m_totalAllocated; }
    size_t getPeakUsage() const { return m_peakUsage; }
    
private:
    MemoryPool() = default;
    ~MemoryPool() = default;
    MemoryPool(const MemoryPool&) = delete;
    MemoryPool& operator=(const MemoryPool&) = delete;
    
    std::vector<MemoryBlock> m_blocks;
    uint8_t* m_pool = nullptr;
    size_t m_poolSize = 0;
    size_t m_totalAllocated = 0;
    size_t m_peakUsage = 0;
    bool m_initialized = false;
};

} // namespace MCOptimizer

#endif // MEMORY_POOL_H
