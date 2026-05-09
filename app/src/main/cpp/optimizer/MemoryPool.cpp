// MinecraftMobileOptimizer/app/src/main/cpp/optimizer/MemoryPool.cpp
#include "MemoryPool.h"
#include <algorithm>
#include <android/log.h>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "MemoryPool", __VA_ARGS__)

MemoryPool::MemoryPool(size_t totalSize) 
    : totalSize_(totalSize)
    , usedSize_(0)
    , poolMemory_(std::make_unique<char[]>(totalSize)) {
    MemoryBlock initialBlock{poolMemory_.get(), totalSize, false, 0};
    blocks_.push_back(initialBlock);
    LOGI("Pool: %.2f MB", totalSize / (1024.0f * 1024.0f));
}

MemoryPool::~MemoryPool() = default;

void* MemoryPool::allocate(size_t size) {
    for (auto& block : blocks_) {
        if (!block.used && block.size >= size) {
            block.used = true;
            usedSize_ += size;
            if (block.size > size + 64) {
                MemoryBlock newBlock{
                    static_cast<char*>(block.ptr) + size,
                    block.size - size,
                    false,
                    block.offset + size
                };
                block.size = size;
                auto it = std::find(blocks_.begin(), blocks_.end(), block);
                blocks_.insert(it + 1, newBlock);
            }
            return block.ptr;
        }
    }
    LOGI("Alloc failed! Need: %zu", size);
    return nullptr;
}

void MemoryPool::free(void* ptr) {
    for (auto& block : blocks_) {
        if (block.ptr == ptr && block.used) {
            block.used = false;
            usedSize_ -= block.size;
            return;
        }
    }
}

void MemoryPool::defragment() {
    for (size_t i = 0; i < blocks_.size() - 1; ++i) {
        if (!blocks_[i].used && !blocks_[i + 1].used) {
            blocks_[i].size += blocks_[i + 1].size;
            blocks_.erase(blocks_.begin() + i + 1);
            --i;
        }
    }
}

void MemoryPool::releaseUnused() { defragment(); }

size_t MemoryPool::getUsedMemory() const { return usedSize_; }
size_t MemoryPool::getFreeMemory() const { return totalSize_ - usedSize_; }

float MemoryPool::getFragmentationRatio() const {
    size_t largestFree = 0;
    for (const auto& block : blocks_) {
        if (!block.used && block.size > largestFree) largestFree = block.size;
    }
    return largestFree > 0 ? 1.0f - (float)largestFree / getFreeMemory() : 0.0f;
}
