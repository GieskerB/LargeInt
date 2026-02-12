#ifndef LARGEINT_GENERAL_COMPARISON_HPP
#define LARGEINT_GENERAL_COMPARISON_HPP

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

#endif //LARGEINT_GENERAL_COMPARISON_HPP
