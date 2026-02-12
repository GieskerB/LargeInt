# include "gtest/gtest.h"

#include "../../include/large_int/large_int.hpp"

TEST(multiplication_tests, multiply_by_one) {
    const LargeInt<8> a{255};
    const LargeInt<8> b{1};
    std::stringstream ss;
    ss << a * b;
    ASSERT_EQ("00ff - [255]", ss.str());
}

TEST(multiplication_tests, multiply_by_zero) {
    const LargeInt<8> a{123};
    const LargeInt<8> b{0};
    std::stringstream ss;
    ss << a * b;
    ASSERT_EQ("0000 - [0]", ss.str());
}

TEST(multiplication_tests, simple_square) {
    const LargeInt<8> a{16};
    const LargeInt<8> b{16};
    std::stringstream ss;
    ss << a * b;
    ASSERT_EQ("0100 - [256]", ss.str());
}

TEST(multiplication_tests, large_product) {
    const LargeInt<8> a{100};
    const LargeInt<8> b{200};
    std::stringstream ss;
    ss << a * b;
    ASSERT_EQ("4e20 - [20000]", ss.str());
}

TEST(multiplication_tests, max_8bit_multiplication) {
    const LargeInt<8> a{255};
    const LargeInt<8> b{255};
    std::stringstream ss;
    ss << a * b;
    ASSERT_EQ("fe01 - [65025]", ss.str());
}