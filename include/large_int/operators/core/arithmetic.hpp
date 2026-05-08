#ifndef LARGE_INT_OPERATORS_CORE_ARITHMETIC_HPP
#define LARGE_INT_OPERATORS_CORE_ARITHMETIC_HPP

#include "large_int/details/burnikel_ziegler.hpp"

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

/*
 * Karatsuba multiplication: Divide and conquer.
 * X×Y = (X_H×Y_H) ≪ 128 + ( (X_L×YH) + (X_H×Y_L) ) ≪ 64 + (X_L×Y_L)
 * => 4 mults, 3 adds, 2 shifts (BAD)
 * X×Y = (X_H×Y_H) ≪ 128 + ( (X_H + X_L)(Y_H + Y_L) − (X_H×Y_H) − (X_L×Y_L) ) ≪ 64 + (X_L×Y_L)
 * => 3 mults, 6 adds, 2 shifts (GOOD)
 */
template<uint16_t N>
LargeInt<2 * N> LargeInt<N>::operator*(const LargeInt<N> &other) const {

    LargeInt<N / 2> sum_this{m_upper};
    sum_this += m_lower;
    const bool carry_this = sum_this.was_overflow();

    LargeInt<N / 2> sum_other{other.m_upper};
    sum_other += other.m_lower;
    const bool carry_other = sum_other.was_overflow();

    const LargeInt<N> &sum_prod{sum_this * sum_other};
    LargeInt<2 * N> special_product{sum_prod};


    if (carry_this) {
        LargeInt<N> term_N{sum_other};
        LargeInt<2 * N> term{term_N}; // Step-by-step to prevent double implicit conversion errors
        term <<= static_cast<uint16_t>(N / 2);
        special_product += term;
    }
    if (carry_other) {
        LargeInt<N> term_N{sum_this};
        LargeInt<2 * N> term{term_N};
        term <<= static_cast<uint16_t>(N / 2);
        special_product += term;
    }
    if (carry_this && carry_other) {
        LargeInt<2 * N> term{1};
        term <<= N;
        special_product += term;
    }

    const LargeInt<N> &upper_times_upper{m_upper * other.m_upper};
    const LargeInt<N> &lower_times_lower{m_lower * other.m_lower};

    special_product -= upper_times_upper;
    special_product -= lower_times_lower;

    special_product <<= static_cast<uint16_t> (N / 2);

    LargeInt<2 * N> result{upper_times_upper, lower_times_lower};
    result += special_product;
    return result;
}

// Burnikel-Ziegler Algorithm
// https://pure.mpg.de/rest/items/item_1819444_4/component/file_2599480/content
template<uint16_t N>
LargeInt<N> LargeInt<N>::operator/(const LargeInt<N> &other) const {
    return bz_algo::div_mod_bz(*this, other).first;
}

template<uint16_t N>
LargeInt<N> LargeInt<N>::operator%(const LargeInt<N> &other) const {
    return bz_algo::div_mod_bz(*this, other).second;
}

template<uint16_t N>
LargeInt<N> LargeInt<N>::operator~() const {
    LargeInt<N> res{*this};
    res.m_upper = ~res.m_upper;
    res.m_lower = ~res.m_lower;
    return res;
}

template<uint16_t N>
LargeInt<N> LargeInt<N>::operator&(const LargeInt<N> &other) const {
    LargeInt<N> res{*this};
    res &= other;
    return res;
}

template<uint16_t N>
LargeInt<N> LargeInt<N>::operator|(const LargeInt<N> &other) const {
    LargeInt<N> res{*this};
    res |= other;
    return res;
}

template<uint16_t N>
LargeInt<N> LargeInt<N>::operator^(const LargeInt<N> &other) const {
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

#endif //LARGE_INT_OPERATORS_CORE_ARITHMETIC_HPP
