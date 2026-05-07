#include "gtest/gtest.h"
#include "../../include/large_int/large_int.hpp"

TEST(LargeIntBitwiseTest, BasicAnd) {
    LargeInt<8> a(15);
    LargeInt<8> b(3);
    auto result = a & b;
    EXPECT_EQ(result, LargeInt<8>(3));
}

TEST(LargeIntBitwiseTest, BasicOr) {
    LargeInt<16> a("43690");
    LargeInt<16> b("17476");
    auto result = a | b;
    EXPECT_EQ(result, LargeInt<16>("61166"));
}

TEST(LargeIntBitwiseTest, BasicXor) {
    LargeInt<32> a("3321733766");
    LargeInt<32> b("4110595839");
    auto result = a ^ b;
    EXPECT_EQ(result, LargeInt<32>("822023289"));
}

TEST(LargeIntBitwiseTest, BitwiseNot) {
    LargeInt<8> a(0);
    auto result = ~a;
    EXPECT_EQ(result, LargeInt<8>(255));
}

TEST(LargeIntBitwiseTest, AndWithZero) {
    LargeInt<64> a("18446744073709551615");
    LargeInt<64> b(0);
    auto result = a & b;
    EXPECT_EQ(result, LargeInt<64>(0));
}

TEST(LargeIntBitwiseTest, OrWithZero) {
    LargeInt<128> a("340282366920938463463374607431768211455");
    LargeInt<128> b(0);
    auto result = a | b;
    EXPECT_EQ(result, LargeInt<128>("340282366920938463463374607431768211455"));
}

TEST(LargeIntBitwiseTest, XorWithSelf) {
    LargeInt<256> a("9999999999999999999999999999999999999999");
    auto result = a ^ a;
    EXPECT_EQ(result, LargeInt<256>(0));
}

TEST(LargeIntBitwiseTest, NotOfMax) {
    LargeInt<32> a("4294967295");
    auto result = ~a;
    EXPECT_EQ(result, LargeInt<32>(0));
}

TEST(LargeIntBitwiseTest, AlternatingBitMask) {
    LargeInt<16> a("43690");
    LargeInt<16> b("21845");
    auto result = a | b;
    EXPECT_EQ(result, LargeInt<16>("65535"));
}

TEST(LargeIntBitwiseTest, DeMorgansLaw) {
    LargeInt<512> a("123456789012345678901234567890");
    LargeInt<512> b("987654321098765432109876543210");

    auto left_side = ~(a | b);
    auto right_side = (~a) & (~b);

    EXPECT_EQ(left_side, right_side);
}