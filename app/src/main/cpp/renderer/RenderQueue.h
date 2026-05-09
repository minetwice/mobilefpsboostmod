// MinecraftMobileOptimizer/app/src/main/cpp/renderer/RenderQueue.h
#pragma once

#include <vector>
#include <cstdint>
#include <mutex>

namespace mcoptimizer {

struct RenderCommand {
    enum Type {
        DRAW_ARRAYS,
        DRAW_ELEMENTS,
        BIND_TEXTURE,
        USE_PROGRAM,
        SET_VIEWPORT,
        CLEAR
    };
    
    Type type;
    union {
        struct { int mode; int first; int count; } drawArrays;
        struct { int mode; int count; int type; const void* indices; } drawElements;
        struct { uint32_t texture; } bindTexture;
        struct { uint32_t program; } useProgram;
        struct { int x; int y; int width; int height; } viewport;
        struct { uint32_t mask; } clear;
    } data;
};

class RenderQueue {
public:
    RenderQueue();
    ~RenderQueue();
    
    void submit(const RenderCommand& cmd);
    void executeAll();
    void clear();
    
    size_t getCommandCount() const;
    
private:
    std::vector<RenderCommand> m_commands;
    mutable std::mutex m_mutex;
};

} // namespace mcoptimizer
