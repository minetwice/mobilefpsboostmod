#include "MemoryPool.h"
#include "utils/Logger.h"
#include <cstring>
#include <algorithm>

namespace MCOptimizer {

MemoryPool& MemoryPool::getInstance() {
    static MemoryPool instance;
    return instance;
}

void* MemoryPool::allocate(size_t size) {
    return getInstance().allocateBlock(size);
}

void MemoryPool::free(void* ptr) {
    getInstance().freeBlock(ptr);
}

void MemoryPool::clear() {
    auto& pool = getInstance();
    Logger::info("MemoryPool", "Clearing memory pool");
    
    for (auto& block : pool.m_blocks) {
        if (block.inUse) {
            std::memset(block.data, 0, block.size);
            block.inUse = false;
        }
    }
    pool.m_totalAllocated = 0;
}

void MemoryPool::optimize() {
    auto& pool = getInstance();
    Logger::info("MemoryPool", "Optimizing memory pool");
    
    // Defragmentation logic
    size_t freedCount = 0;
    for (auto it = pool.m_blocks.begin(); it != pool.m_blocks.end();) {
        if (!it->inUse) {
            it = pool.m_blocks.erase(it);
            freedCount++;
        } else {
            ++it;
        }
    }
    
    Logger::info("MemoryPool", "Freed %zu unused blocks", freedCount);
}

void MemoryPool::initialize(size_t poolSize) {
    if (m_initialized) return;
    
    Logger::info("MemoryPool", "Initializing memory pool with size: %zu bytes", poolSize);
    
    m_pool = new uint8_t[poolSize];
    m_poolSize = poolSize;
    std::memset(m_pool, 0, poolSize);
    m_initialized = true;
}

void MemoryPool::destroy() {
    if (!m_initialized) return;
    
    Logger::info("MemoryPool", "Destroying memory pool");
    
    delete[] m_pool;
    m_pool = nullptr;
    m_poolSize = 0;
    m_blocks.clear();
    m_initialized = false;
}

void* MemoryPool::allocateBlock(size_t size) {
    if (!m_initialized) {
        initialize(1024 * 1024 * 64); // Default 64MB pool
    }
    
    // Find or create a block
    for (auto& block : m_blocks) {
        if (!block.inUse && block.size >= size) {
            block.inUse = true;
            m_totalAllocated += block.size;
            m_peakUsage = std::max(m_peakUsage, m_totalAllocated);
            return block.data;
        }
    }
    
    // Create new block
    MemoryBlock newBlock;
    newBlock.size = size;
    newBlock.inUse = true;
    
    // Simple allocation from pool
    size_t offset = 0;
    for (const auto& block : m_blocks) {
        offset += block.size;
    }
    
    if (offset + size > m_poolSize) {
        Logger::warning("MemoryPool", "Pool exhausted, allocating externally");
        newBlock.data = malloc(size);
    } else {
        newBlock.data = m_pool + offset;
    }
    
    m_blocks.push_back(newBlock);
    m_totalAllocated += size;
    m_peakUsage = std::max(m_peakUsage, m_totalAllocated);
    
    return newBlock.data;
}

void MemoryPool::freeBlock(void* ptr) {
    for (auto& block : m_blocks) {
        if (block.data == ptr && block.inUse) {
            block.inUse = false;
            m_totalAllocated -= block.size;
            
            // Free external allocations
            if (reinterpret_cast<uint8_t*>(ptr) < m_pool || 
                reinterpret_cast<uint8_t*>(ptr) >= m_pool + m_poolSize) {
                free(ptr);
                block.data = nullptr;
            }
            return;
        }
    }
}

} // namespace MCOptimizer
