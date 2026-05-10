#ifndef LARGE_INT_OPERATORS_CORE_COMPARISON_HPP
#define LARGE_INT_OPERATORS_CORE_COMPARISON_HPP

/** @file comparison.hpp */

template<uint16_t N>
bool LargeInt<N>::operator==(const LargeInt<N> &other) const {
    return std::is_eq(*this <=> other);
}


template<uint16_t N>
std::strong_ordering LargeInt<N>::operator<=>(const LargeInt<N> &other) const {
    auto ordering = m_upper <=> other.m_upper;
    if (ordering == std::strong_ordering::equal or ordering == std::strong_ordering::equivalent) {
        return m_lower <=> other.m_lower;
    }
    return ordering;
}

#endif //LARGE_INT_OPERATORS_CORE_COMPARISON_HPP
