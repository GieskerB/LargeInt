#include <gtest/gtest.h>
#include <sstream>
#include "../../include/large_int/large_int.hpp"

TEST(output_tests, print_0) {
    LargeInt<32> num{0};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("00000000 - [0]", ss.str());
}

TEST(output_tests, print_65535) {
    LargeInt<32> num{"65535"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("0000ffff - [65535]", ss.str());
}

TEST(output_tests, print_65536) {
    LargeInt<32> num{"65536"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("00010000 - [65536]", ss.str());
}

TEST(output_tests, print_1234567) {
    LargeInt<32> num{"1234567"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("0012d687 - [1234567]", ss.str());
}

TEST(output_tests, print_0x12345678) {
    LargeInt<32> num{"305419896"};
    std::stringstream ss;
    ss << num;
    // 305419896 is 0x12345678
    EXPECT_EQ("12345678 - [305419896]", ss.str());
}

TEST(output_tests, print_uint_32_max) {
    LargeInt<32> num{"4294967295"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("ffffffff - [4294967295]", ss.str());
}
