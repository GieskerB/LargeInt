//
// Created by bjarn on 19.01.2025.
//

#ifndef LARGEINT_SPECIFIC_COMPARISON_HPP
#define LARGEINT_SPECIFIC_COMPARISON_HPP

bool LargeInt<8>::operator==(const LargeInt<8> &other) const {
    return std::is_eq(m_value <=> other.m_value);
}

std::strong_ordering LargeInt<8>::operator<=>(const LargeInt<8> &other) const {
    return m_value <=> other.m_value;
}

#endif //LARGEINT_SPECIFIC_COMPARISON_HPP
