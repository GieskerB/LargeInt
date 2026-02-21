include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(ArithmeticTests add.cpp mul_bytes.cpp
        shift_ints.cpp)

target_link_libraries(ArithmeticTests gtest gtest_main)
#target_link_libraries(ArithmeticTests large_int)
