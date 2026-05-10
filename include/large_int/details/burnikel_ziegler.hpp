#ifndef LARGE_INT_DETAILS_BURNIKEL_ZIEGLER_HPP
#define LARGE_INT_DETAILS_BURNIKEL_ZIEGLER_HPP

/** @file burnikel_ziegler.hpp */

#include "../large_int.hpp"

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


#endif //LARGE_INT_DETAILS_BURNIKEL_ZIEGLER_HPP
