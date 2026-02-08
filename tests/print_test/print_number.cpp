#include <sstream>
#include "gtest/gtest.h"

#include "LargeInt.hpp"

TEST(print_8,test_eq) {
    LargeInt<8> li{123};
    std::stringstream ss;
    ss << li;
    EXPECT_EQ(ss.str(),"123");
}

TEST(print_16,test_eq) {
    LargeInt<16> li{248};
    std::stringstream ss;
    ss << li;
    EXPECT_EQ(ss.str(),"248");
}

TEST(print_32,test_eq) {
    LargeInt<32> li{3};
    std::stringstream ss;
    ss << li;
    EXPECT_EQ(ss.str(),"3");
}

TEST(print_64,test_eq) {
    LargeInt<64> li{69};
    std::stringstream ss;
    ss << li;
    EXPECT_EQ(ss.str(),"69");
}