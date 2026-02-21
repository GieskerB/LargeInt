# include "gtest/gtest.h"

#include "../../include/large_int/large_int.hpp"

TEST(output_tests, print_13) {
    LargeInt<16> num{13};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("000d - [13]", ss.str());
}

TEST(output_tests, print_135) {
    LargeInt<16> num{135};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("0087 - [135]", ss.str());
}

TEST(output_tests, print_250) {
    LargeInt<16> num{250};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("00fa - [250]", ss.str());
}

TEST(output_tests, print_345) {
    LargeInt<16> num{"345"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("0159 - [345]", ss.str());
}

TEST(output_tests, print_2222) {
    LargeInt<16> num{"2222"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("08ae - [2222]", ss.str());
}

TEST(output_tests, print_10000) {
    LargeInt<16> num{"10000"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("2710 - [10000]", ss.str());
}

TEST(output_tests, print_53199) {
    LargeInt<16> num{"53199"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("cfcf - [53199]", ss.str());
}
