include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(ArithmeticTests
        add.cpp
        sub.cpp
        mul.cpp
        div.cpp
        mod.cpp
        shift_ints.cpp
        bitwise.cpp)

target_link_libraries(ArithmeticTests gtest gtest_main)
