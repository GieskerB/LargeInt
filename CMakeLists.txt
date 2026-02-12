cmake_minimum_required(VERSION 3.30)
project(LargeInt
    VERSION 0.7
    DESCRIPTION "A possibly infinite large integer in C++ based on 8bit arithmetic."
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

add_compile_definitions(DEBUG_PRINT)
#add_compile_definitions(BINARY_PRINT)

add_executable(LargeInt main.cpp)

add_subdirectory(tests)



