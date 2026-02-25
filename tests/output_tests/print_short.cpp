#include <gtest/gtest.h>
#include <sstream>
#include "../../include/large_int/large_int.hpp"

TEST(output_tests_short, print_0) {
    LargeInt<16> num{0};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("0000 - [0]", ss.str());
}


TEST(output_tests_short, print_13) {
    LargeInt<16> num{13};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("000d - [13]", ss.str());
}

TEST(output_tests_short, print_135) {
    LargeInt<16> num{135};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("0087 - [135]", ss.str());
}

TEST(output_tests_short, print_255) {
    LargeInt<16> num{255};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("00ff - [255]", ss.str());
}

TEST(output_tests_short, print_256) {
    LargeInt<16> num{"256"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("0100 - [256]", ss.str());
}

TEST(output_tests_short, print_345) {
    LargeInt<16> num{"345"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("0159 - [345]", ss.str());
}

TEST(output_tests_short, print_2222) {
    LargeInt<16> num{"2222"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("08ae - [2222]", ss.str());
}

TEST(output_tests_short, print_10000) {
    LargeInt<16> num{"10000"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("2710 - [10000]", ss.str());
}

TEST(output_tests_short, print_53199) {
    LargeInt<16> num{"53199"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("cfcf - [53199]", ss.str());
}

TEST(output_tests_short, print_max) {
    LargeInt<16> num{"65535"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("ffff - [65535]", ss.str());
}
