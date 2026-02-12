# include "gtest/gtest.h"

#include "../../include/large_int/large_int.hpp"

TEST(addition_tests, add_numbers) {
    const LargeInt<8> a{3};
    const LargeInt<8> b{5};
    std::stringstream ss;
    ss << a + b;
    ASSERT_EQ("08 - [8]", ss.str());
}

TEST(addition_tests, add_zero) {
    const LargeInt<8> a{42};
    const LargeInt<8> b{0};
    std::stringstream ss;
    ss << a + b;
    ASSERT_EQ("2a - [42]", ss.str());
}

TEST(addition_tests, max_value_no_overflow) {
    const LargeInt<8> a{200};
    const LargeInt<8> b{55};
    std::stringstream ss;
    ss << a + b;
    ASSERT_EQ("ff - [255]", ss.str());
}

TEST(addition_tests, overflow_to_zero) {
    const LargeInt<8> a{255};
    const LargeInt<8> b{1};
    std::stringstream ss;
    ss << a + b;
    ASSERT_EQ("00 - [0]", ss.str());
}

TEST(addition_tests, large_wrap_around) {
    const LargeInt<8> a{150};
    const LargeInt<8> b{150};
    // 150 + 150 = 300. 300 % 256 = 44. Hex of 44 is 2c.
    std::stringstream ss;
    ss << a + b;
    ASSERT_EQ("2c - [44]", ss.str());
}

