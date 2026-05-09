# MinecraftMobileOptimizer/app/src/main/cpp/CMakeLists.txt
cmake_minimum_required(VERSION 3.22.1)
project("mcoptimizer" VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler flags for performance
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -ffast-math -funroll-loops")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fomit-frame-pointer -DNDEBUG")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

# Find packages
find_package(Vulkan QUIET)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/core
    ${CMAKE_SOURCE_DIR}/renderer
    ${CMAKE_SOURCE_DIR}/optimizer
    ${CMAKE_SOURCE_DIR}/hooks
    ${CMAKE_SOURCE_DIR}/utils
)

# Source files
set(CORE_SOURCES
    core/Engine.cpp
)

set(RENDERER_SOURCES
    renderer/VulkanRenderer.cpp
    renderer/GLInterceptor.cpp
    renderer/RenderQueue.cpp
)

set(OPTIMIZER_SOURCES
    optimizer/FramePacer.cpp
    optimizer/MemoryPool.cpp
    optimizer/TextureCache.cpp
)

set(HOOKS_SOURCES
    hooks/GLHooks.cpp
    hooks/EGLHooks.cpp
)

set(UTILS_SOURCES
    utils/Logger.cpp
    utils/Timer.cpp
    utils/ThreadPool.cpp
)

set(ALL_SOURCES
    native-lib.cpp
    ${CORE_SOURCES}
    ${RENDERER_SOURCES}
    ${OPTIMIZER_SOURCES}
    ${HOOKS_SOURCES}
    ${UTILS_SOURCES}
)

# Create shared library
add_library(mcoptimizer SHARED ${ALL_SOURCES})

# Link libraries
set(LINK_LIBRARIES
    android
    log
    EGL
    GLESv3
    jnigraphics
)

if(Vulkan_FOUND)
    list(APPEND LINK_LIBRARIES Vulkan::Vulkan)
    target_compile_definitions(mcoptimizer PRIVATE HAS_VULKAN=1)
    message(STATUS "Vulkan support enabled")
else()
    message(STATUS "Vulkan not found, using OpenGL ES fallback")
endif()

target_link_libraries(mcoptimizer ${LINK_LIBRARIES})

# Strip symbols in release
set_target_properties(mcoptimizer PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
)
