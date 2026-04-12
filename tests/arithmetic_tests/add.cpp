# include "gtest/gtest.h"

#include "../../include/large_int/large_int.hpp"

TEST(LargeIntTest, BasicAddition) {
    LargeInt<8> a(10);
    LargeInt<8> b(20);
    a += b;
    EXPECT_EQ(a, LargeInt<8>(30));
}

TEST(LargeIntTest, IdentityProperty) {
    LargeInt<64> a("12345678901234567890");
    LargeInt<64> b(0);
    a += b;
    EXPECT_EQ(a, LargeInt<64>("12345678901234567890"));
}

TEST(LargeIntTest, SimpleCarry) {
    LargeInt<16> a(255);
    LargeInt<16> b(1);
    a += b;
    EXPECT_EQ(a, LargeInt<16>("256"));
}

TEST(LargeIntTest, OverflowWrapAround) {
    // For N=8, Max is 255. 255 + 1 should be 0.
    LargeInt<8> a(255);
    LargeInt<8> b(1);
    a += b;
    EXPECT_EQ(a, LargeInt<8>(0));
}

TEST(LargeIntTest, LongCarryChain) {
    LargeInt<128> a("340282366920938463463374607431768211455"); // 2^128 - 1
    LargeInt<128> b(1);
    a += b;
    EXPECT_EQ(a, LargeInt<128>(0));
}

TEST(LargeIntTest, MaxPlusMax) {
    LargeInt<64> a("18446744073709551615");
    LargeInt<64> b("18446744073709551615");
    a += b;
    EXPECT_EQ(a, LargeInt<64>("18446744073709551614"));
}

TEST(LargeIntTest, MiddleBitCarry) {
    LargeInt<32> a("65535");
    LargeInt<32> b(1);
    a += b;
    EXPECT_EQ(a, LargeInt<32>("65536"));
}

TEST(LargeIntTest, SelfAddition) {
    LargeInt<256> a("500");
    a += a;
    EXPECT_EQ(a, LargeInt<256>("1000"));
}

TEST(LargeIntTest, LoopAddition) {
    LargeInt<64> a(0);
    LargeInt<64> b("10000");
    for(int i = 0; i < 100000; ++i) {
        a += b;
    }
    EXPECT_EQ(a, LargeInt<64>("1000000000"));
}

TEST(LargeIntTest, VeryLargeValues) {
    LargeInt<256> a("1447406582488280158790859206340347915387605139893881069817716699586621391737");
    LargeInt<256> b("213991609661492377197829821996354348797467160465561955622007450784842178439");
    a += b;
    EXPECT_EQ(a, LargeInt<256>("1661398192149772535988689028336702264185072300359443025439724150371463570176"));
}
