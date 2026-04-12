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

/**
 * Karatsuba multiplication: Divide and conquer.
 * X×Y = (X_H×Y_H) ≪ 128 + ( (X_L×YH) + (X_H×Y_L) ) ≪ 64 + (X_L×Y_L)
 * => 4 mults, 3 adds, 2 shifts (BAD)
 * X×Y = (X_H×Y_H) ≪ 128 + ( (X_H + X_L)(Y_H + Y_L) − (X_H×Y_H) − (X_L×Y_L) ) ≪ 64 + (X_L×Y_L)
 * => 3 mults, 6 adds, 2 shifts (GOOD)
 *
 * @param other
 * @return
 */
template<uint16_t N>
LargeInt<2 * N> LargeInt<N>::operator*(const LargeInt<N> &other) const {

    LargeInt<N / 2> sum_this {m_upper};
    sum_this += m_lower;
    const bool carry_this = sum_this.was_overflow();

    LargeInt<N / 2> sum_other {other.m_upper};
    sum_other += other.m_lower;
    const bool carry_other = sum_other.was_overflow();

    const LargeInt<N>& sum_prod {sum_this * sum_other};
    LargeInt<2 * N> special_product {sum_prod};


    if (carry_this) {
        LargeInt<N> term_N {sum_other};
        LargeInt<2 * N> term {term_N}; // Step-by-step to prevent double implicit conversion errors
        term <<= static_cast<uint16_t>(N / 2);
        special_product += term;
    }
    if (carry_other) {
        LargeInt<N> term_N {sum_this};
        LargeInt<2 * N> term {term_N};
        term <<= static_cast<uint16_t>(N / 2);
        special_product += term;
    }
    if (carry_this && carry_other) {
        LargeInt<2 * N> term {1};
        term <<= N;
        special_product += term;
    }

    const LargeInt<N>& upper_times_upper {m_upper * other.m_upper};
    const LargeInt<N>& lower_times_lower {m_lower * other.m_lower};

    special_product -= upper_times_upper;
    special_product -= lower_times_lower;

    special_product <<= static_cast<uint16_t> (N / 2);

    LargeInt<2 * N> result{upper_times_upper,lower_times_lower};
    result += special_product;
    return result;
}

inline std::pair<LargeInt<8>,LargeInt<16>> div_three_halves_by_two(const LargeInt<8> &a1, const LargeInt<8> &a2, const LargeInt<8> &a3, const LargeInt<8> &b1, const LargeInt<8> &b2) {

    const LargeInt<16>a12{a1,a2};
    const LargeInt<16>B{b1,b2};

    LargeInt<8> q = (a12 / b1).m_lower; // 16o information lost
    LargeInt<8> c = (a12 - q * b1).m_lower; // Apparently no information loss either
    LargeInt<16> D = q * b2;
    auto R = LargeInt<16>(c,a3)-D;
    if(R.was_underflow()) { // q is too large by at least one
        q--;
        R+=B;

        if(R.was_underflow()) { // q is still too large
            q--;
            R+= B; // new R is correct
        }
    }
    return {q, R};
}

template<uint16_t N>
std::pair<LargeInt<N/2>,LargeInt<N>> div_three_halves_by_two(const LargeInt<N/2> &a1, const LargeInt<N/2> &a2, const LargeInt<N/2> &a3, const LargeInt<N/2> &b1, const LargeInt<N/2> &b2) {

    const LargeInt<N>a12{a1,a2};
    const LargeInt<N>B{b1,b2};

    LargeInt<N/2> q = (a12 / b1).m_lower; // No information lost
    LargeInt<N/2> c = (a12 - q * b1).m_lower; // Apparently no information loss either
    LargeInt<N> D = q * b2;
    auto R = LargeInt<N>(c,a3)-D;
    if(R.was_underflow()) { // q is too large by at least one
        q--;
        R+=B;

        if(R.was_underflow()) { // q is still too large
            q--;
            R+= B; // new R is correct
        }
    }
    return {q, R};
}

inline std::pair<LargeInt<8>,LargeInt<8>> div_two_digits_by_one(const LargeInt<8> &AH, const LargeInt<8> &AL, const LargeInt<8> &B) {
    const uint16_t A = AH.m_value << 8 | AL.m_value;
    return {A / B.m_value, A % B.m_value};
}

template<uint16_t N>
std::pair<LargeInt<N>,LargeInt<N>> div_two_digits_by_one(const LargeInt<N> &AH, const LargeInt<N> &AL, const LargeInt<N> &B) {
    const LargeInt<N/2> &a1 = AH.m_upper;
    const LargeInt<N/2> &a2 = AH.m_lower;
    const LargeInt<N/2> &a3 = AL.m_upper;
    const LargeInt<N/2> &a4 = AL.m_lower;
    const LargeInt<N/2> &b1 = B.m_upper;
    const LargeInt<N/2> &b2 = B.m_lower;

    std::pair<LargeInt<N/2>,LargeInt<N>> q1R = div_three_halves_by_two(a1,a2,a3,b1,b2);
    const LargeInt<N/2> &r1 = q1R.second.m_upper;
    const LargeInt<N/2> &r2 = q1R.second.m_lower;
    std::pair<LargeInt<N/2>,LargeInt<N>> q2S = div_three_halves_by_two(r1, r2, a4, b1, b2);
    const LargeInt<N> Q (q1R.first, q2S.first);

    return {Q, q2S.second};
}

// TODO Division: Burnikel-Ziegler Algorithm
// https://pure.mpg.de/rest/items/item_1819444_4/component/file_2599480/content
template<uint16_t  N>
LargeInt<N> LargeInt<N>::operator/(const LargeInt<N>& other) const{
    auto pair = div_two_digits_by_one(m_upper,m_lower, other.m_lower);
    return LargeInt<N>(pair.first);
}

template<uint16_t  N>
LargeInt<N> LargeInt<N>::operator%(const LargeInt<N>& other) const{
    auto pair = div_two_digits_by_one(m_upper,m_lower, other.m_lower);
    return LargeInt<N>(pair.second);
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
