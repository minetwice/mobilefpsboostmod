// MinecraftMobileOptimizer/app/src/main/cpp/optimizer/MemoryPool.h
#pragma once
#include <cstddef>
#include <vector>
#include <memory>

struct MemoryBlock {
    void* ptr;
    size_t size;
    bool used;
    size_t offset;
};

class MemoryPool {
public:
    explicit MemoryPool(size_t totalSize);
    ~MemoryPool();
    void* allocate(size_t size);
    void free(void* ptr);
    void defragment();
    void releaseUnused();
    size_t getUsedMemory() const;
    size_t getFreeMemory() const;
    float getFragmentationRatio() const;
private:
    size_t totalSize_;
    size_t usedSize_;
    std::vector<MemoryBlock> blocks_;
    std::unique_ptr<char[]> poolMemory_;
};
