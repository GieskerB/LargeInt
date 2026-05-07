#include <gtest/gtest.h>
#include <sstream>
#include "../../include/large_int/large_int.hpp"

TEST(output_tests_long, print_0) {
    LargeInt<64> num{0};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("0000000000000000 - [0]", ss.str());
}

TEST(output_tests_long, print_255) {
    LargeInt<64> num{255};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("00000000000000ff - [255]", ss.str());
}

TEST(output_tests_long, print_4294967295) {
    LargeInt<64> num{"4294967295"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("00000000ffffffff - [4294967295]", ss.str());
}

TEST(output_tests_long, print_4294967296) {
    LargeInt<64> num{"4294967296"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("0000000100000000 - [4294967296]", ss.str());
}

TEST(output_tests_long, print_1000000000000) {
    LargeInt<64> num{"1000000000000"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("000000e8d4a51000 - [1000000000000]", ss.str());
    // 000000e8d4a51000 - [1000000000000]
    // 0000000005f5e100 - [100000000]
}

TEST(output_tests_long, print_0x123456789abcdef) {
    LargeInt<64> num{"81985529216486895"};
    std::stringstream ss;
    ss << num;
    // 0x0123456789abcdef
    EXPECT_EQ("0123456789abcdef - [81985529216486895]", ss.str());
}

TEST(output_tests_long, print_0x0101010101010101) {
    LargeInt<64> num{"72340172838076673"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("0101010101010101 - [72340172838076673]", ss.str());
}

TEST(output_tests_long, print_2_to_the_63) {
    LargeInt<64> num{"9223372036854775808"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("8000000000000000 - [9223372036854775808]", ss.str());
}

TEST(output_tests_long, print_near_max) {
    LargeInt<64> num{"18446744073709551610"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("fffffffffffffffa - [18446744073709551610]", ss.str());
}

TEST(output_tests_long, print_max) {
    LargeInt<64> num{"18446744073709551615"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("ffffffffffffffff - [18446744073709551615]", ss.str());
}
