# include "gtest/gtest.h"

#include "../../include/large_int/large_int.hpp"

TEST(output_tests_byte, print_byte_0) {
    LargeInt<8> num{0};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("00 - [0]", ss.str());
}

TEST(output_tests_byte, print_byte_1) {
    LargeInt<8> num{1};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("01 - [1]", ss.str());
}

TEST(output_tests_byte, print_byte_2) {
    LargeInt<8> num{2};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("02 - [2]", ss.str());
}

TEST(output_tests_byte, print_byte_3) {
    LargeInt<8> num{3};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("03 - [3]", ss.str());
}

TEST(output_tests_byte, print_byte_10) {
    LargeInt<8> num{10};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("0a - [10]", ss.str());
}

TEST(output_tests_byte, print_byte_15) {
    LargeInt<8> num{15};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("0f - [15]", ss.str());
}

TEST(output_tests_byte, print_byte_32) {
    LargeInt<8> num{32};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("20 - [32]", ss.str());
}

TEST(output_tests_byte, print_byte_63) {
    LargeInt<8> num{63};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("3f - [63]", ss.str());
}

TEST(output_tests_byte, print_byte_100) {
    LargeInt<8> num{100};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("64 - [100]", ss.str());
}

TEST(output_tests_byte, print_byte_max) {
    LargeInt<8> num{255};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("ff - [255]", ss.str());
}
