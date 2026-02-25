#include <gtest/gtest.h>
#include <sstream>
#include "../../include/large_int/large_int.hpp"

TEST(output_tests_large, print_0) {
    LargeInt<128> num{"0"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("00000000000000000000000000000000", ss.str());
}

TEST(output_tests_large, print_128_mid_pattern) {
    LargeInt<128> num{"18446744073709551616"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("00000000000000010000000000000000", ss.str());
    // 000000000000000010000000000000000
    //  00000000000000010000000000000000
}

TEST(output_tests_large, print_128_alternating) {
    // 0x55...55 (128 bits = 32 nibbles)
    LargeInt<128> num{"113707792182908852866924704746725171797"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("558b52fdf416eab21e0f4dde8773e255", ss.str());
}

// 4. N=256: Single Bit in High Word
TEST(output_tests_large, print_256_high_word) {
    // 2^252
    LargeInt<256> num{"7237005577332262213973186563042994240829374041602535252466099000494570602496"};
    std::stringstream ss;
    ss << num;
    // Starts with 0x1... followed by 63 zeros
    std::string expected = "1" + std::string(63, '0');
    EXPECT_EQ(expected, ss.str());
}

// 5. N=256: Full "F" Pattern
TEST(output_tests_large, print_256_max) {
    LargeInt<256> num{"115792089237316195423570985008687907853269984665640564039457584007913129639935"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ(std::string(64, 'f'), ss.str());
}

// 6. N=512: Leading Zero Padding check
TEST(output_tests_large, print_512_small_value) {
    LargeInt<512> num{"4096"}; // 0x1000
    std::stringstream ss;
    ss << num;
    // 128 hex digits total
    std::string expected = std::string(124, '0') + "1000";
    EXPECT_EQ(expected, ss.str());
}

TEST(output_tests_large, print_256_pattern_A) {
    LargeInt<256> num{"7719465253958304130007357386001222883445899658231024345229654761401344234026"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("11110ffffffffc7b1ccaef24a10b26fb95ce495508844070ff57242735d6922a", ss.str());
}

TEST(output_tests_large, print_128_sparse) {
    LargeInt<128> num{"170141183460469231731687303715884105729"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("80000000000000000000000000000001", ss.str());
}

TEST(output_tests_large, print_256_offset_pattern) {
    // Value shifted to sit in the middle of a 256-bit int
    LargeInt<256> num{"84914198774031876643952055673037799092397988754803080295602228272469628402619"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ(std::string(64,'b'), ss.str());
}

TEST(output_tests_large, print_funny_words) {
    LargeInt<512> num{"19774869593635345467511446977894956051781113933337530787016454603198236789754977737792297279473141627211661965042695405436928"};
    std::stringstream ss;
    ss << num;
    EXPECT_EQ("0000000000000000000000001dea0000b1050000bad0000babe0000beef0000c0ffee0000cafe0000d15ea5e0000dead0000f00d0000f0cacc1a0000face0000", ss.str());
}