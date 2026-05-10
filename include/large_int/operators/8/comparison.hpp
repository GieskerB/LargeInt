#ifndef LARGE_INT_OPERATORS_8_COMPARISON_HPP
#define LARGE_INT_OPERATORS_8_COMPARISON_HPP

/** @file comparison.hpp */

inline bool LargeInt<8>::operator==(const LargeInt<8> &other) const {
    return std::is_eq(m_value <=> other.m_value);
}

inline std::strong_ordering LargeInt<8>::operator<=>(const LargeInt<8> &other) const {
    return m_value <=> other.m_value;
}

#endif //LARGE_INT_OPERATORS_8_COMPARISON_HPP
