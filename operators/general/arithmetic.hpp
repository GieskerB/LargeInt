//
// Created by bjarn on 19.01.2025.
//

#ifndef LARGEINT_GENERAL_ARITHMETIC_HPP
#define LARGEINT_GENERAL_ARITHMETIC_HPP

// TODO 13

template<uint16_t N>
LargeInt<N> LargeInt<N>::operator+() const {
    return *this;
}

template<uint16_t N>
LargeInt<N> LargeInt<N>::operator-() const {
    throw std::runtime_error("Can not invert LargeInt due to being unsigned");
}

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

template<uint16_t  N>
LargeInt<N> LargeInt<N>::operator%(const LargeInt<N>& other) const{
    LargeInt<N> res{*this};
    res %= other;
    return res;
}

template<uint16_t  N>
LargeInt<N> LargeInt<N>::operator~() const{
    LargeInt<N> res{*this};
    res.m_upper = ~res.m_upper;
    res.m_lower = ~res.m_lower;
    return res;
}
template<uint16_t  N>
LargeInt<N> LargeInt<N>::operator&(const LargeInt<N>& other) const{
    LargeInt<N> res{*this};
    res &= other;
    return res;
}
template<uint16_t  N>
LargeInt<N> LargeInt<N>::operator|(const LargeInt<N>& other) const{
    LargeInt<N> res{*this};
    res |= other;
    return res;
}
template<uint16_t  N>
LargeInt<N> LargeInt<N>::operator^(const LargeInt<N>& other) const{
    LargeInt<N> res{*this};
    res ^= other;
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

#endif //LARGEINT_GENERAL_ARITHMETIC_HPP
