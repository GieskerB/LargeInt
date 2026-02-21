include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(OutputTests print_byte.cpp print_short.cpp
        print_int.cpp)

target_link_libraries(OutputTests gtest gtest_main)
#target_link_libraries(OutputTests large_int)
