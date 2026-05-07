cmake_minimum_required(VERSION 3.10)
project(LargeInt
        VERSION 0.7
        DESCRIPTION "A possibly infinite large integer in C++ based on 8bit arithmetic."
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(DEBUG_PRINT)
#add_compile_definitions(BINARY_PRINT)

include_directories(include)

add_executable(LargeInt main.cpp)

add_subdirectory(tests)