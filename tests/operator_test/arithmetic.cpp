#include "gtest/gtest.h"

#include <sstream>
#include "LargeInt.hpp"

TEST(addition1,test_eq) {
    LargeInt<32> a{222},b{175};
    LargeInt<32> c{a+b};
    std::stringstream ss;
    ss << c;
    EXPECT_EQ(ss.str(),"397");
}

TEST(addition2,test_eq) {
    LargeInt<32> a{200},b{100},c{99},d{246};
    LargeInt<32> e{a+b+c+d};
    std::stringstream ss;
    ss << e;
    EXPECT_EQ(ss.str(),"645");
}

TEST(addition3,test_eq) {
    LargeInt<32> a{125},b{202};
    for (int i = 0; i< 1000; i++) {
        a += b;
    }
    std::stringstream ss;
    ss << a;
    EXPECT_EQ(ss.str(),"202125");
}