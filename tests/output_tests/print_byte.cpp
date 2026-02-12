# include "gtest/gtest.h"

#include "../../include/large_int/large_int.hpp"

TEST(output_tests, print_num) {
    LargeInt<8> num{0};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("00 - [0]", ss.str());
}

TEST(output_tests, print_three) {
    LargeInt<8> num{3};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("03 - [3]", ss.str());
}

TEST(output_tests, print_14) {
    LargeInt<8> num{14};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("0e - [14]", ss.str());
}

TEST(output_tests, print_100) {
    LargeInt<8> num{100};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("64 - [100]", ss.str());
}

TEST(output_tests, print_255) {
    LargeInt<8> num{255};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("ff - [255]", ss.str());
}