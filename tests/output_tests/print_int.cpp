#include <gtest/gtest.h>
#include <sstream>
#include "../../include/large_int/large_int.hpp"

TEST(output_tests_int, print_0) {
    LargeInt<32> num{0};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("00000000 - [0]", ss.str());
}

TEST(output_tests_int, print_7777) {
    LargeInt<32> num{"7777"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("00001e61 - [7777]", ss.str());
}

TEST(output_tests_int, print_12345) {
    LargeInt<32> num{"12345"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("00003039 - [12345]", ss.str());
}

TEST(output_tests_int, print_65535) {
    LargeInt<32> num{"65535"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("0000ffff - [65535]", ss.str());
}

TEST(output_tests_int, print_65536) {
    LargeInt<32> num{"65536"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("00010000 - [65536]", ss.str());
}

TEST(output_tests_int, print_41256098) {
    LargeInt<32> num{"41256098"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("027584a2 - [41256098]", ss.str());
}

TEST(output_tests_int, print_12345678) {
    LargeInt<32> num{"1234567"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("0012d687 - [1234567]", ss.str());
}

TEST(output_tests_int, print_87654321) {
    LargeInt<32> num{"87654321"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("05397fb1 - [87654321]", ss.str());
}

TEST(output_tests_int, print_0x12345678) {
    LargeInt<32> num{"305419896"};
    std::stringstream ss;
    ss << num;
    // 305419896 is 0x12345678
    EXPECT_EQ("12345678 - [305419896]", ss.str());
}

TEST(output_tests_int, print_max) {
    LargeInt<32> num{"4294967295"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("ffffffff - [4294967295]", ss.str());
}
