# MinecraftMobileOptimizer/mod/src/main/cpp/CMakeLists.txt
cmake_minimum_required(VERSION 3.22.1)
project("mcoptimizer-mod-bridge" VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# JNI headers
find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})

set(SOURCES
    jni-bridge.cpp
    optimizer-native.cpp
)

add_library(mcoptimizermod SHARED ${SOURCES})

target_link_libraries(mcoptimizermod
    ${JNI_LIBRARIES}
)
