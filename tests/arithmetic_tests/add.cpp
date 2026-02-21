# include "gtest/gtest.h"

#include "../../include/large_int/large_int.hpp"

// 1. Basic Addition (Small Scale)
TEST(LargeIntTest, BasicAddition) {
    LargeInt<8> a(10);
    LargeInt<8> b(20);
    a += b;
    EXPECT_EQ(a, LargeInt<8>(30));
}

// 2. Identity Property (Adding Zero)
TEST(LargeIntTest, IdentityProperty) {
    LargeInt<64> a("12345678901234567890");
    LargeInt<64> b(0);
    a += b;
    EXPECT_EQ(a, LargeInt<64>("12345678901234567890"));
}

// 3. Simple Carry Propagation
// Testing if 1 + 255 triggers a carry in an 8-bit boundary
TEST(LargeIntTest, SimpleCarry) {
    LargeInt<16> a(255);
    LargeInt<16> b(1);
    a += b;
    EXPECT_EQ(a, LargeInt<16>("256"));
}

// 4. Maximum Value + 1 (Overflow Handling)
// Standard behavior for unsigned large ints is to wrap around (modulo 2^N)
TEST(LargeIntTest, OverflowWrapAround) {
    // For N=8, Max is 255. 255 + 1 should be 0.
    LargeInt<8> a(255);
    LargeInt<8> b(1);
    a += b;
    EXPECT_EQ(a, LargeInt<8>(0));
}

// 5. Large Carry Chain (N=128)
// Ensures the carry propagates through multiple internal words
TEST(LargeIntTest, LongCarryChain) {
    // FFFFFFFF... + 1
    LargeInt<128> a("340282366920938463463374607431768211455"); // 2^128 - 1
    LargeInt<128> b(1);
    a += b;
    EXPECT_EQ(a, LargeInt<128>(0));
}

// 6. Max Value to Max Value (N=64)
// (2^64 - 1) + (2^64 - 1) should result in (2^64 - 2) due to overflow
TEST(LargeIntTest, MaxPlusMax) {
    LargeInt<64> a("18446744073709551615");
    LargeInt<64> b("18446744073709551615");
    a += b;
    // Expected: 2^65 - 2, but wrapped to 64 bits is 2^64 - 2
    EXPECT_EQ(a, LargeInt<64>("18446744069414584318"));
}

// 7. Middle Bit Carry (N=32)
// Testing carry exactly at the 16-bit mark
TEST(LargeIntTest, MiddleBitCarry) {
    LargeInt<32> a("65535"); // 0xFFFF
    LargeInt<32> b(1);
    a += b;
    EXPECT_EQ(a, LargeInt<32>("65536")); // 0x10000
}

// 8. Self-Addition (a += a)
TEST(LargeIntTest, SelfAddition) {
    LargeInt<256> a("500");
    a += a;
    EXPECT_EQ(a, LargeInt<256>("1000"));
}

// 9. Repeated Small Additions (Stress Test)
TEST(LargeIntTest, LoopAddition) {
    LargeInt<64> a(0);
    LargeInt<64> b(1);
    for(int i = 0; i < 1000; ++i) {
        a += b;
    }
    EXPECT_EQ(a, LargeInt<64>("1000"));
}

// 10. Large Values Near Limit (N=256)
TEST(LargeIntTest, VeryLargeValues) {
    std::string val1 = "115792089237316195423570985008687907853269984665640564039457584007913129639935"; // 2^256 - 1
    LargeInt<256> a(val1);
    LargeInt<256> b(5);
    a += b;
    // Should wrap to 4
    EXPECT_EQ(a, LargeInt<256>(4));
}

