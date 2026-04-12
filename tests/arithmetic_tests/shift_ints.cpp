# include "gtest/gtest.h"

#include "../../include/large_int/large_int.hpp"

TEST(shift_tests, shift_left_one) {
    const LargeInt<32> a{1};
    std::stringstream ss;
    ss << (a << 1);
    ASSERT_EQ("00000002 - [2]", ss.str());
}

TEST(shift_tests, shift_into_next_nibble) {
    const LargeInt<32> a{16};
    std::stringstream ss;
    ss << (a << 4);
    ASSERT_EQ("00000100 - [256]", ss.str());
}

TEST(shift_tests, large_power_of_two) {
    const LargeInt<32> a{1};
    std::stringstream ss;
    ss << (a << 16);
    ASSERT_EQ("00010000 - [65536]", ss.str());
}

TEST(shift_tests, shift_to_upper_boundary) {
    const LargeInt<32> a{255};
    std::stringstream ss;
    ss << (a << 24);
    ASSERT_EQ("ff000000 - [4278190080]", ss.str());
}

TEST(shift_tests, shift_overflow_to_zero) {
    const LargeInt<32> a{1};
    std::stringstream ss;
    ss << (a << 32);
    ASSERT_EQ("00000000 - [0]", ss.str());
}

TEST(edge_case_tests, crawl_bits_across_boundary) {
    LargeInt<32> a{170};
    a <<= 7;
    a += LargeInt<32>{1};
    a <<= 13;

    std::stringstream ss;
    ss << a;
    ASSERT_EQ("0aa02000 - [178266112]", ss.str());
}

TEST(edge_case_tests , fill_lower_and_shift) {
    LargeInt<32> a{255};
    a <<= 9;
    a += LargeInt<32>{255};
    a <<= 3;

    std::stringstream ss;
    ss << a;
    ASSERT_EQ("000ff7f8 - [1046520]", ss.str());
}

TEST(edge_case_tests, odd_shift_accumulation) {
    LargeInt<32> a{127};
    a <<= 1;
    a += LargeInt<32>{1};
    a <<= 1;
    a += LargeInt<32>{1};
    a <<= 17;

    std::stringstream ss;
    ss << a;
    ASSERT_EQ("03fe0000 - [66977792]", ss.str());
}

TEST(edge_case_tests, bit_pop_to_upper_half) {
    LargeInt<32> a{128};
    a <<= 8;
    a += LargeInt<32>{1};
    a <<= 1;

    std::stringstream ss;
    ss << a;
    ASSERT_EQ("00010002 - [65538]", ss.str());
}

TEST(edge_case_tests, complex_interleaved_fragmentation) {
    LargeInt<32> a{200};
    a <<= 11;
    a += LargeInt<32>{100};
    a <<= 5;
    a += LargeInt<32>{50};
    a <<= 3;

    std::stringstream ss;
    ss << a;
    ASSERT_EQ("06406590 - [104883600]", ss.str());
}