#include "gtest/gtest.h"
#include "../../include/large_int/large_int.hpp"

// 1. Basic Division
TEST(LargeIntDivTest, BasicDivision) {
    LargeInt<8> a(100);
    LargeInt<8> b(20);
    auto result = a / b;
    EXPECT_EQ(result, LargeInt<8>(5));
}

// 2. Identity Division
TEST(LargeIntDivTest, IdentityDivision) {
    LargeInt<32> a("4294967200");
    LargeInt<32> b(1);
    auto result = a / b;
    EXPECT_EQ(result, LargeInt<32>("4294967200"));
}

// 3. Self Division
TEST(LargeIntDivTest, SelfDivision) {
    LargeInt<64> a("18446744073709551610");
    LargeInt<64> b("18446744073709551610");
    auto result = a / b;
    EXPECT_EQ(result, LargeInt<64>(1));
}

// 4. Truncating Division
TEST(LargeIntDivTest, TruncatingDivision) {
    LargeInt<16> a(100);
    LargeInt<16> b(3);
    auto result = a / b;
    EXPECT_EQ(result, LargeInt<16>(33));
}

// 5. Zero Numerator
TEST(LargeIntDivTest, ZeroNumerator) {
    LargeInt<128> a(0);
    LargeInt<128> b("340282366920938463463374607431768211455");
    auto result = a / b;
    EXPECT_EQ(result, LargeInt<128>(0));
}

// 6. Large Dividend, Small Divisor
TEST(LargeIntDivTest, LargeSmallDivision) {
    LargeInt<128> a("10000000000000000000000000000000000000");
    LargeInt<128> b(2);
    auto result = a / b;
    EXPECT_EQ(result, LargeInt<128>("5000000000000000000000000000000000000"));
}

// 7. Small Dividend, Large Divisor
TEST(LargeIntDivTest, SmallLargeDivision) {
    LargeInt<64> a(50);
    LargeInt<64> b("18446744073709551610");
    auto result = a / b;
    EXPECT_EQ(result, LargeInt<64>(0));
}

// 8. Power of Two Division
TEST(LargeIntDivTest, PowerOfTwoDivision) {
    LargeInt<256> a("1048576"); // 2^20
    LargeInt<256> b("1024");    // 2^10
    auto result = a / b;
    EXPECT_EQ(result, LargeInt<256>("1024"));
}

// 9. Maximum Value Halving
TEST(LargeIntDivTest, MaxValueHalving) {
    LargeInt<32> a("4294967295");
    LargeInt<32> b(2);
    auto result = a / b;
    EXPECT_EQ(result, LargeInt<32>("2147483647"));
}

// 10. Massive Scale Division
TEST(LargeIntDivTest, MassiveScaleDivision) {
    LargeInt<512> a("88888888888888888888888888888888888888888888888888");
    LargeInt<512> b("2222222222222222222222222");
    auto result = a / b;
    EXPECT_EQ(result, LargeInt<512>("40000000000000000000000004"));
}