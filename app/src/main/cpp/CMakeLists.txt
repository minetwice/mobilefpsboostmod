cmake_minimum_required(VERSION 3.18.1)

project("mcoptimizer")

# Find required packages
find_package(log REQUIRED)

# Add source files
set(SOURCES
    native-lib.cpp
    renderer/VulkanRenderer.cpp
    renderer/GLInterceptor.cpp
    optimizer/FramePacer.cpp
    optimizer/MemoryPool.cpp
    utils/Logger.cpp
)

# Create shared library
add_library(mcoptimizer SHARED ${SOURCES})

# Include directories
target_include_directories(mcoptimizer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/renderer
    ${CMAKE_CURRENT_SOURCE_DIR}/optimizer
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
)

# Link libraries
target_link_libraries(mcoptimizer
    android
    log
    EGL
    GLESv3
)

# Compiler flags
target_compile_options(mcoptimizer PRIVATE
    -Wall
    -Wextra
    -std=c++17
    -O2
)
