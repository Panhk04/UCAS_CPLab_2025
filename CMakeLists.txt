cmake_minimum_required(VERSION 3.5)

project(Compiler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)

# 查找 LLVM
find_package(LLVM REQUIRED CONFIG)

# 添加 LLVM 包含目录
include_directories(${LLVM_INCLUDE_DIRS})

# 添加 LLVM 定义
add_definitions(${LLVM_DEFINITIONS})


include_directories(deps/antlr4-runtime/)
include_directories(grammar)
include_directories(src)


FILE(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "grammar/*.cpp")

FILE(GLOB_RECURSE ANTLR_LIB_FILES "deps/antlr4-runtime/*.cpp")

add_definitions(-w -g)
add_library(antlr STATIC ${ANTLR_LIB_FILES})

add_executable(compiler ${SOURCE_FILES})
find_package(Threads REQUIRED)
target_link_libraries(compiler antlr Threads::Threads)

llvm_map_components_to_libnames(llvm_libs support core irreader)
target_link_libraries(compiler ${llvm_libs})