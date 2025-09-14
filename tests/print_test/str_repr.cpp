#include "gtest/gtest.h"
#include <sstream>
#include "LargeInt.hpp"

TEST(str_to_8bit1, test_eq) {
    const std::string value {"123"};
    LargeInt<8> li {value};
    std::stringstream ss;
    ss << li;
    EXPECT_EQ(value, ss.str());
}

TEST(str_to_8bit2, test_eq) {
    const std::string value {"7"};
    LargeInt<8> li {value};
    std::stringstream ss;
    ss << li;
    EXPECT_EQ(value, ss.str());
}

TEST(str_to_8bit3, test_eq) {
    const std::string value {""};
    LargeInt<8> li {value};
    std::stringstream ss;
    ss << li;
    EXPECT_EQ("0", ss.str());
}

TEST(str_to_16bit1, test_eq) {
    const std::string value {"32123"};
    LargeInt<16> li {value};
    std::stringstream ss;
    ss << li;
    EXPECT_EQ(value, ss.str());
}

TEST(str_to_16bit2, test_eq) {
    const std::string value {"12345"};
    LargeInt<16> li {value};
    std::stringstream ss;
    ss << li;
    EXPECT_EQ(value, ss.str());
}

TEST(str_to_16bit3, test_eq) {
    const std::string value {""};
    LargeInt<16> li {value};
    std::stringstream ss;
    ss << li;
    EXPECT_EQ("0", ss.str());
}

TEST(str_to_64bit1, test_eq) {
    const std::string value {"125"};
    LargeInt<64> li {value};
    std::stringstream ss;
    ss << li;
    EXPECT_EQ(value, ss.str());
}

TEST(str_to_64bit2, test_eq) {
    const std::string value {"192837465"};
    LargeInt<64> li {value};
    std::stringstream ss;
    ss << li;
    EXPECT_EQ(value, ss.str());
}

TEST(str_to_64bit3, test_eq) {
    const std::string value {"18446744073709551615"};
    LargeInt<64> li {value};
    std::stringstream ss;
    ss << li;
    EXPECT_EQ(value, ss.str());
}