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

namespace bz_algo {
// -----------------------------------------------------------------------------------------
// Algorithm 1: Div3n2n
// Divides a 3n-bit integer by a 2n-bit integer
// -----------------------------------------------------------------------------------------
    template<uint16_t N>
    std::pair<LargeInt<N / 2>, LargeInt<N>>
    div_3n_2n(const LargeInt<N> &A_12, const LargeInt<N / 2> &A_3, const LargeInt<N> &B) {
        LargeInt<N / 2> B_1 = B.m_upper;
        LargeInt<N / 2> B_2 = B.m_lower;

        LargeInt<N / 2> Q;
        LargeInt<N / 2> R_1;
        bool carry_R1 = false;

        // Step 1: Estimate Q
        if (A_12.m_upper < B_1) {
            auto res = div_2n_1n<N>(A_12, B_1);
            Q = res.first;
            R_1 = res.second;
        } else {
            Q = ~LargeInt<N / 2>{0}; // Max value (all 1s)
            LargeInt<N / 2> tmp = A_12.m_lower;
            tmp += B_1;
            carry_R1 = tmp.was_overflow();
            R_1 = tmp;
        }

        // Step 2: Calculate remainder and correct Q
        LargeInt<N> R_part1{R_1, A_3};
        LargeInt<2*N> Q_B2 = LargeInt<N>{Q} * LargeInt<N>{B_2};

        LargeInt<N> R = R_part1 - Q_B2.m_lower;

        // If R_1 overflowed earlier, R_part1 is technically much larger, so no borrow happens.
        bool borrow = carry_R1 ? false : (R_part1 < Q_B2);

        // Correction step (runs at most twice in standard BZ)
        while (borrow) {
            --Q;
            LargeInt<N> old_R = R;
            R += B;
            if (R < old_R) borrow = false; // Underflow resolved via wrap-around
        }

        return {Q, R};
    }

// -----------------------------------------------------------------------------------------
// Algorithm 2: Div2n1n
// Divides a 2n-bit integer by an n-bit integer
// -----------------------------------------------------------------------------------------
    template<uint16_t N>
    std::pair<LargeInt<N / 2>, LargeInt<N / 2>> div_2n_1n(const LargeInt<N> &A, const LargeInt<N / 2> &B) {
        LargeInt<N / 2> A_12 = A.m_upper;
        LargeInt<N / 4> A_3 = A.m_lower.m_upper;
        LargeInt<N / 4> A_4 = A.m_lower.m_lower;

        auto step1 = bz_algo::div_3n_2n<N / 2>(A_12, A_3, B);
        LargeInt<N / 4> Q_1 = step1.first;
        LargeInt<N / 2> R_1 = step1.second;

        auto step2 = bz_algo::div_3n_2n<N / 2>(R_1, A_4, B);
        LargeInt<N / 4> Q_2 = step2.first;
        LargeInt<N / 2> R_2 = step2.second;

        LargeInt<N / 2> Q{Q_1, Q_2};
        return {Q, R_2};
    }

// Base case specialization to stop recursion at N=16 (calling native 8-bit division)
    template<>
    inline std::pair<LargeInt<8>, LargeInt<8>> div_2n_1n<16>(const LargeInt<16> &A, const LargeInt<8> &B) {
        // Safe extraction avoiding dependency on 'to_decimal' include order
        uint16_t a_val = (static_cast<uint16_t>(static_cast<uint64_t>(A.m_upper)) << 8) |
                         static_cast<uint16_t>(static_cast<uint64_t>(A.m_lower));
        uint8_t b_val = static_cast<uint8_t>(static_cast<uint64_t>(B));

        uint8_t q = a_val / b_val;
        uint8_t r = a_val % b_val;
        return {LargeInt<8>{q}, LargeInt<8>{r}};
    }

// TODO Division: Burnikel-Ziegler Algorithm
// https://pure.mpg.de/rest/items/item_1819444_4/component/file_2599480/content
    template<uint16_t N>
    std::pair<LargeInt<N>, LargeInt<N>> div_mod_bz(const LargeInt<N> &numerator, const LargeInt<N> &denominator) {
        if (denominator == LargeInt<N>{0}) throw std::runtime_error("Division by zero");
        if (numerator < denominator) return {LargeInt<N>{0}, numerator};

        // 1. Normalize the divisor (Shift until MSB is 1)
        uint16_t shift = 0;
        LargeInt<N> D = denominator;
        LargeInt<N> msb_mask = LargeInt<N>{1};
        msb_mask <<= (N - 1);

        while ((D & msb_mask) == LargeInt<N>{0}) {
            D <<= 1;
            shift++;
        }

        // 2. Shift the numerator without losing highest bits (Virtual 2N extension)
        LargeInt<N> A_high = (shift == 0) ? LargeInt<N>{0} : (numerator >> (N - shift));
        LargeInt<N> A_low = numerator << shift;

        // 3. Unroll top-level 2N / N block division using exactly two 3n/2n steps
        LargeInt<N> A_12 = A_high;
        LargeInt<N / 2> A_3 = A_low.m_upper;
        LargeInt<N / 2> A_4 = A_low.m_lower;

        auto step1 = bz_algo::div_3n_2n<N>(A_12, A_3, D);
        LargeInt<N / 2> Q_upper = step1.first;
        LargeInt<N> R_1 = step1.second;

        auto step2 = bz_algo::div_3n_2n<N>(R_1, A_4, D);
        LargeInt<N / 2> Q_lower = step2.first;
        LargeInt<N> R_final = step2.second;

        LargeInt<N> Q{Q_upper, Q_lower};

        // 4. Un-normalize the remainder
        LargeInt<N> R = R_final >> shift;

        return {Q, R};
    }
}

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

#endif //LARGEINT_GENERAL_ARITHMETIC_HPP
