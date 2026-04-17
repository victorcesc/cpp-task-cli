cmake_minimum_required(VERSION 3.16)
project(learn-modern-cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(learn-modern-cpp
    src/main.cpp
    src/Task.cpp
)

target_include_directories(learn-modern-cpp PRIVATE src)

add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
)