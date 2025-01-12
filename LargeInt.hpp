//
// Created by bjarn on 27.12.2024.
//

#ifndef TESTING_LARGEINT_HPP
#define TESTING_LARGEINT_HPP

#include "LargeInt_general.hpp"
#include "LargeInt_specific.hpp"

// =====================================================================================================================

//TODO PRINTING


std::ostream &operator<<(std::ostream &os, LargeInt<8> large_int) {
    os << +large_int.m_value;
    return os;
}

std::ostream &operator<<(std::ostream &os, LargeInt<16> large_int) {
    os << (+large_int.m_upper.m_value << 8) + +large_int.m_lower.m_value;
    return os;
}

std::ostream &operator<<(std::ostream &os, LargeInt<32> large_int) {
    os << (+large_int.m_upper.m_upper.m_value << 24) + (+large_int.m_upper.m_lower.m_value << 16) +
          (+large_int.m_lower.m_upper.m_value << 8) + +large_int.m_lower.m_lower.m_value;
    return os;
}

std::ostream &operator<<(std::ostream &os, LargeInt<64> large_int) {
    os << ((unsigned long long) large_int.m_upper.m_upper.m_upper.m_value << 56) +
          ((unsigned long long) large_int.m_upper.m_upper.m_lower.m_value << 48) +
          ((unsigned long long) large_int.m_upper.m_lower.m_upper.m_value << 40) +
          ((unsigned long long) large_int.m_lower.m_upper.m_lower.m_value << 32) +
          (+large_int.m_lower.m_upper.m_upper.m_value << 24) + (+large_int.m_lower.m_upper.m_lower.m_value << 16) +
          (+large_int.m_lower.m_lower.m_upper.m_value << 8) + +large_int.m_lower.m_lower.m_lower.m_value;
    return os;
}

#endif //TESTING_LARGEINT_HPP
