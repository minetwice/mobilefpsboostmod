// MinecraftMobileOptimizer/app/src/main/cpp/renderer/RenderQueue.cpp
#include "RenderQueue.h"
#include <GLES3/gl3.h>
#include <android/log.h>

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "RenderQueue", __VA_ARGS__)

namespace mcoptimizer {

RenderQueue::RenderQueue() = default;
RenderQueue::~RenderQueue() = default;

void RenderQueue::submit(const RenderCommand& cmd) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_commands.push_back(cmd);
}

void RenderQueue::executeAll() {
    std::vector<RenderCommand> commands;
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        commands = std::move(m_commands);
        m_commands.clear();
    }
    
    for (const auto& cmd : commands) {
        switch (cmd.type) {
            case RenderCommand::DRAW_ARRAYS:
                glDrawArrays(cmd.data.drawArrays.mode, 
                           cmd.data.drawArrays.first, 
                           cmd.data.drawArrays.count);
                break;
                
            case RenderCommand::DRAW_ELEMENTS:
                glDrawElements(cmd.data.drawElements.mode,
                             cmd.data.drawElements.count,
                             cmd.data.drawElements.type,
                             cmd.data.drawElements.indices);
                break;
                
            case RenderCommand::BIND_TEXTURE:
                glBindTexture(GL_TEXTURE_2D, cmd.data.bindTexture.texture);
                break;
                
            case RenderCommand::USE_PROGRAM:
                glUseProgram(cmd.data.useProgram.program);
                break;
                
            case RenderCommand::SET_VIEWPORT:
                glViewport(cmd.data.viewport.x, cmd.data.viewport.y,
                          cmd.data.viewport.width, cmd.data.viewport.height);
                break;
                
            case RenderCommand::CLEAR:
                glClear(cmd.data.clear.mask);
                break;
        }
    }
}

void RenderQueue::clear() {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_commands.clear();
}

size_t RenderQueue::getCommandCount() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_commands.size();
}

} // namespace mcoptimizer
