#include "gtest/gtest.h"
#include "../../include/large_int/large_int.hpp"

// 1. Basic Modulo
TEST(LargeIntModTest, BasicModulo) {
    LargeInt<8> a(100);
    LargeInt<8> b(30);
    auto result = a % b;
    EXPECT_EQ(result, LargeInt<8>(10));
}

// 2. Identity Modulo
TEST(LargeIntModTest, IdentityModulo) {
    LargeInt<32> a("4294967200");
    LargeInt<32> b("4294967200");
    auto result = a % b;
    EXPECT_EQ(result, LargeInt<32>(0));
}

// 3. Modulo One
TEST(LargeIntModTest, ModuloOne) {
    LargeInt<64> a("18446744073709551610");
    LargeInt<64> b(1);
    auto result = a % b;
    EXPECT_EQ(result, LargeInt<64>(0));
}

// 4. Modulo Two (Even)
TEST(LargeIntModTest, ModuloTwoEven) {
    LargeInt<128> a("340282366920938463463374607431768211454"); // Ends in 4, even
    LargeInt<128> b(2);
    auto result = a % b;
    EXPECT_EQ(result, LargeInt<128>(0));
}

// 5. Modulo Two (Odd)
TEST(LargeIntModTest, ModuloTwoOdd) {
    LargeInt<128> a("340282366920938463463374607431768211455"); // Max value is odd
    LargeInt<128> b(2);
    auto result = a % b;
    EXPECT_EQ(result, LargeInt<128>(1));
}

// 6. Zero Numerator
TEST(LargeIntModTest, ZeroNumerator) {
    LargeInt<64> a(0);
    LargeInt<64> b("500");
    auto result = a % b;
    EXPECT_EQ(result, LargeInt<64>(0));
}

// 7. Small Modulo Large
TEST(LargeIntModTest, SmallModuloLarge) {
    LargeInt<64> a(50);
    LargeInt<64> b("18446744073709551610");
    auto result = a % b;
    EXPECT_EQ(result, LargeInt<64>(50));
}

// 8. Max Value Modulo Max-1
TEST(LargeIntModTest, MaxModuloMaxMinusOne) {
    LargeInt<32> a("4294967295");
    LargeInt<32> b("4294967294");
    auto result = a % b;
    EXPECT_EQ(result, LargeInt<32>(1));
}

// 9. Power of 10 Wrap
TEST(LargeIntModTest, PowerOfTenWrap) {
    LargeInt<256> a("1234567890");
    LargeInt<256> b("1000");
    auto result = a % b;
    EXPECT_EQ(result, LargeInt<256>("890"));
}

// 10. Massive Scale Modulo
TEST(LargeIntModTest, MassiveScaleModulo) {
    LargeInt<512> a("100000000000000000000000000000000000000000055");
    LargeInt<512> b("1000");
    auto result = a % b;
    EXPECT_EQ(result, LargeInt<512>("55"));
}