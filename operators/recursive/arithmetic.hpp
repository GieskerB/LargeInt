//
// Created by bjarn on 19.01.2025.
//

#ifndef LARGEINT_RECURSIVE_ARITHMETIC_HPP
#define LARGEINT_RECURSIVE_ARITHMETIC_HPP

// TODO 13
// Unary +
// Unary -
// Unary ~
// Binary %
// Binary &
// Binary |
// Binary ^

template<uint16_t N>
LargeInt<N> LargeInt<N>::operator+(const LargeInt<N> &other) const {
    LargeInt<N> res{*this};
    res += other;
    return res;
}

template<uint16_t N>
LargeInt<N> LargeInt<N>::operator-(const LargeInt<N> &other) const {
    LargeInt<N> res{*this};
    res -= other;
    return res;
}

template<uint16_t N>
LargeInt<2 * N> LargeInt<N>::operator*(const LargeInt<N> &other) const {
    const LargeInt<N>& upper_times_upper = m_upper * other.m_upper;
    const LargeInt<N>& lower_times_lower = m_lower * other.m_lower;
    LargeInt<2 * N> special_product{(m_upper + m_lower) * (other.m_upper + other.m_lower)};

    LargeInt<2 * N> result{};
    result.m_upper = upper_times_upper;
    result.m_lower = lower_times_lower;
    result.initialize_pointers();

    special_product -= lower_times_lower;
    special_product -= upper_times_upper;
    special_product <<= N / 2;
    result += special_product;
    return result;
}

template<uint16_t  N>
LargeInt<N> LargeInt<N>::operator/(const LargeInt<N>& other) const{
    LargeInt<N> res{*this};
    res /= other;
    return res;
}

template<uint16_t N>
LargeInt<N> LargeInt<N>::operator<<(uint16_t shift) const {
    LargeInt<N> res{*this};
    res <<= shift;
    return res;
}

template<uint16_t N>
LargeInt<N> LargeInt<N>::operator>>(uint16_t shift) const {
    LargeInt<N> res{*this};
    res >>= shift;
    return res;
}

#endif //LARGEINT_RECURSIVE_ARITHMETIC_HPP
