# include "gtest/gtest.h"

#include "../../include/large_int/large_int.hpp"

// 1. Basic Widening (8-bit to 16-bit)
TEST(LargeIntMulTest, WideningSmall) {
    LargeInt<8> a(16);
    LargeInt<8> b(16);
    auto result = a * b;
    // Type should be LargeInt<16>
    EXPECT_EQ(result, LargeInt<16>("256"));
}

// 2. Maximum Value Preservation (8-bit)
TEST(LargeIntMulTest, MaxValueWidening) {
    LargeInt<8> a(255); // Max 8-bit
    LargeInt<8> b(255);
    auto result = a * b; // 255 * 255 = 65025
    EXPECT_EQ(result, LargeInt<16>("65025"));
}

// 3. Middle-Range Widening (32-bit to 64-bit)
TEST(LargeIntMulTest, MidRangeWidening) {
    LargeInt<32> a("65535");      // 65535
    LargeInt<32> b("65537");     // 65537
    auto result = a * b;         // 4,294,967,295 (Max 32-bit value)
    EXPECT_EQ(result, LargeInt<64>("4294967295"));
}

// 4. Power of 2 Boundary (16-bit to 32-bit)
TEST(LargeIntMulTest, BoundaryCrossing) {
    LargeInt<16> a("256");
    LargeInt<16> b("256");
    auto result = a * b; // 65536 (Requires 17th bit, fits in 32-bit)
    EXPECT_EQ(result, LargeInt<32>("65536"));
}

// 5. Large Scale Widening (64-bit to 128-bit)
TEST(LargeIntMulTest, LargeScaleWidening) {
    LargeInt<64> a("4294967296"); // 2^32
    LargeInt<64> b("4294967296"); // 2^32
    auto result = a * b;
    // Result is 2^64, which exceeds 64-bit but fits 128-bit
    EXPECT_EQ(result, LargeInt<128>("18446744073709551616"));
}

// 6. Identity with Type Promotion
TEST(LargeIntMulTest, IdentityPromotion) {
    LargeInt<16> a("12345");
    LargeInt<16> b(1);
    auto result = a * b;
    // Result must be LargeInt<32> even if value fits in 16
    EXPECT_EQ(result, LargeInt<32>("12345"));
}

// 7. Multiplication by Zero Widening
TEST(LargeIntMulTest, ZeroWidening) {
    LargeInt<32> a("99999999");
    LargeInt<32> b(0);
    auto result = a * b;
    EXPECT_EQ(result, LargeInt<64>(0));
}

// 8. Distributive Property across Widened Types
TEST(LargeIntMulTest, DistributiveWidening) {
    LargeInt<16> a(10);
    LargeInt<16> b(20);
    LargeInt<16> c(30);
    // (a * b) and (a * c) both return LargeInt<32>
    auto leftSide = a * (b + c);
    auto rightSide = (a * b) + (a * c);
    EXPECT_EQ(leftSide, rightSide);
}

// 9. Squaring the Absolute Max (128-bit to 256-bit)
TEST(LargeIntMulTest, ExtremeWidening) {
    LargeInt<64> a("18446744073709551615");
    auto result = a * a;
    // (2^64 - 1)^2 = 2^128 - 2^65 + 1
    EXPECT_EQ(result, LargeInt<128>("340282366920938463426481119284349108225"));
}

// 10. Bitwise Alignment Check
TEST(LargeIntMulTest, BitAlignment) {
    // Multiply 0x1 (bit 0) by 0x1 (bit 0) in 8-bit
    LargeInt<8> a(128);
    LargeInt<8> b(128);
    auto result = a * b;
    EXPECT_EQ(result, LargeInt<16>("16384"));
}