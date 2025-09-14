//
// Created by bjarn on 19.01.2025.
//

#ifndef LARGEINT_ATOMIC_COMPARISON_HPP
#define LARGEINT_ATOMIC_COMPARISON_HPP

inline bool LargeInt<8>::operator==(const LargeInt<8> &other) const {
    return std::is_eq(m_value <=> other.m_value);
}

inline std::strong_ordering LargeInt<8>::operator<=>(const LargeInt<8> &other) const {
    return m_value <=> other.m_value;
}

#endif //LARGEINT_ATOMIC_COMPARISON_HPP
