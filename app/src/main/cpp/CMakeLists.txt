# MinecraftMobileOptimizer/app/src/main/cpp/CMakeLists.txt
cmake_minimum_required(VERSION 3.22.1)
project("mcoptimizer")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Vulkan)

set(SOURCES
    native-lib.cpp
    renderer/VulkanRenderer.cpp
    renderer/GLInterceptor.cpp
    optimizer/FramePacer.cpp
    optimizer/MemoryPool.cpp
    utils/Logger.cpp
)

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/renderer
    ${CMAKE_SOURCE_DIR}/optimizer
    ${CMAKE_SOURCE_DIR}/utils
)

add_library(mcoptimizer SHARED ${SOURCES})

target_link_libraries(mcoptimizer
    android
    log
    EGL
    GLESv3
)

if(Vulkan_FOUND)
    target_link_libraries(mcoptimizer Vulkan::Vulkan)
    target_compile_definitions(mcoptimizer PRIVATE HAS_VULKAN=1)
endif()

target_compile_options(mcoptimizer PRIVATE
    -O3
    -ffast-math
    -funroll-loops
    -fomit-frame-pointer
    -DNDEBUG
)
