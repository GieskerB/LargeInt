#include "gtest/gtest.h"

#include "../../include/large_int/large_int.hpp"

// 1. Basic Subtraction
TEST(LargeIntSubTest, BasicSubtraction) {
    LargeInt<8> a(50);
    LargeInt<8> b(20);
    a -= b;
    EXPECT_EQ(a, LargeInt<8>(30));
}

// 2. Identity Property
TEST(LargeIntSubTest, IdentityProperty) {
    LargeInt<64> a("12345678901234567890");
    LargeInt<64> b(0);
    a -= b;
    EXPECT_EQ(a, LargeInt<64>("12345678901234567890"));
}

// 3. Zero Result
TEST(LargeIntSubTest, ZeroResult) {
    LargeInt<128> a("340282366920938463463374607431768211455");
    LargeInt<128> b("340282366920938463463374607431768211455");
    a -= b;
    EXPECT_EQ(a, LargeInt<128>(0));
}

// 4. Underflow Wrap Around
TEST(LargeIntSubTest, UnderflowWrapAround) {
    // 0 - 1 should wrap to the maximum value of the type
    LargeInt<8> a(0);
    LargeInt<8> b(1);
    a -= b;
    EXPECT_EQ(a, LargeInt<8>(255));
}

// 5. Long Borrow Chain
TEST(LargeIntSubTest, LongBorrowChain) {
    LargeInt<64> a(0);
    LargeInt<64> b(1);
    a -= b;
    EXPECT_EQ(a, LargeInt<64>("18446744073709551615")); // 2^64 - 1
}

// 6. Middle Bit Borrow
TEST(LargeIntSubTest, MiddleBitBorrow) {
    // 65536 is 1 0000 0000 0000 0000 in binary. Subtracting 1 forces a borrow across boundaries.
    LargeInt<32> a("65536");
    LargeInt<32> b(1);
    a -= b;
    EXPECT_EQ(a, LargeInt<32>("65535"));
}

// 7. Max Value Subtraction
TEST(LargeIntSubTest, MaxValueSubtraction) {
    LargeInt<32> a("4294967295"); // Max 32-bit
    LargeInt<32> b("4294967294");
    a -= b;
    EXPECT_EQ(a, LargeInt<32>(1));
}

// 8. Cascading Borrow Edge Case
TEST(LargeIntSubTest, CascadingBorrowEdgeCase) {
    LargeInt<256> a("10000000000000000000000000000000000000000"); // Very large clean number
    LargeInt<256> b(1);
    a -= b;
    EXPECT_EQ(a, LargeInt<256>("9999999999999999999999999999999999999999"));
}

// 9. Loop Subtraction
TEST(LargeIntSubTest, LoopSubtraction) {
    LargeInt<64> a("1000000000");
    LargeInt<64> b("10000");
    for(int i = 0; i < 100000; ++i) {
        a -= b;
    }
    EXPECT_EQ(a, LargeInt<64>(0));
}

// 10. Massive Bounds
TEST(LargeIntSubTest, MassiveBounds) {
    LargeInt<512> a("987654321098765432109876543210");
    LargeInt<512> b("123456789012345678901234567890");
    a -= b;
    EXPECT_EQ(a, LargeInt<512>("864197532086419753208641975320"));
}