#ifndef LARGE_INT_CORE_HPP
#define LARGE_INT_CORE_HPP

namespace bz_algo {
    template<uint16_t N>
    std::pair<LargeInt<N/2>, LargeInt<N/2>> div_2n_1n(const LargeInt<N>& A, const LargeInt<N/2>& B);

    template<uint16_t N>
    std::pair<LargeInt<N/2>, LargeInt<N>> div_3n_2n(const LargeInt<N>& A_12, const LargeInt<N/2>& A_3, const LargeInt<N>& B);

    template<uint16_t N>
    std::pair<LargeInt<N>, LargeInt<N>> div_mod_bz(const LargeInt<N>& numerator, const LargeInt<N>& denominator);
}

template<uint16_t N>
class LargeInt {
    template<uint16_t M> friend class LargeInt;
    friend uint64_t to_decimal(const LargeInt<16>&);
    friend uint64_t to_decimal(const LargeInt<32>&);
    friend uint64_t to_decimal(const LargeInt<64>&);
    template<uint16_t M> friend void output_hex(std::ostream& os, const LargeInt<M>& number, uint16_t base);
    template<uint16_t M> friend void output_bin(std::ostream& os, const LargeInt<M>& number, uint16_t base);
    template<uint16_t M> friend std::pair<LargeInt<M/2>, LargeInt<M/2>> bz_algo::div_2n_1n(const LargeInt<M>& A, const LargeInt<M/2>& B);
    template<uint16_t M> friend std::pair<LargeInt<M/2>, LargeInt<M>> bz_algo::div_3n_2n(const LargeInt<M>& A_12, const LargeInt<M/2>& A_3, const LargeInt<M>& B);
    template<uint16_t M> friend std::pair<LargeInt<M>, LargeInt<M>> bz_algo::div_mod_bz(const LargeInt<M>& numerator, const LargeInt<M>& denominator);


    static_assert(N >= 8 , "LargeInt size must be at least one byte in size");
    static_assert((N & (N - 1)) == 0, "LargeInt size must be a power of 2 for recursive splitting");

    LargeInt<N / 2> m_upper, m_lower;
    bool m_overflown, m_underflown;
    const branch_side_t c_branch_side;

    LargeInt<2 * N> *p_parent;

    LargeInt(uint8_t, branch_side_t);
    LargeInt(const LargeInt<N / 2> &);
    LargeInt(const LargeInt<N / 2> &, int);
    LargeInt(const LargeInt<N / 2> &,const LargeInt<N / 2> &);

    void initialize_pointers(LargeInt<2 * N> * = nullptr, LargeInt<8>** = nullptr);
    void multiply_by_ten(uint8_t carry = 0);

public:
    LargeInt();
    LargeInt(uint8_t);
    LargeInt(const LargeInt &);
    explicit LargeInt (const std::string&);

    bool was_overflow();
    bool was_underflow();

    // arithmetic
    LargeInt<N> operator+(const LargeInt<N> &) const;
    LargeInt<N> operator-(const LargeInt<N> &) const;
    LargeInt<2*N> operator*(const LargeInt<N> &) const;
    LargeInt<N> operator/(const LargeInt<N> &) const;
    LargeInt<N> operator%(const LargeInt<N> &) const;
    LargeInt<N> operator~() const;
    LargeInt<N> operator&(const LargeInt<N> &) const;
    LargeInt<N> operator|(const LargeInt<N> &) const;
    LargeInt<N> operator^(const LargeInt<N> &) const;
    LargeInt<N> operator<<(uint16_t) const;
    LargeInt<N> operator>>(uint16_t) const;

    // assignment
    LargeInt<N> &operator=(const LargeInt &);
    LargeInt<N> &operator+=(const LargeInt<N> &);
    LargeInt<N> &operator-=(const LargeInt<N> &);
    LargeInt<N> &operator*=(const LargeInt<N> &);
    LargeInt<N> &operator/=(const LargeInt<N> &);
    LargeInt<N> &operator%=(const LargeInt<N> &);
    LargeInt<N> &operator&=(const LargeInt<N> &);
    LargeInt<N> &operator|=(const LargeInt<N> &);
    LargeInt<N> &operator^=(const LargeInt<N> &);
    LargeInt<N> &operator<<=(uint16_t);
    LargeInt<N> &operator>>=(uint16_t);

    // comparison
    bool operator==(const LargeInt<N> &) const;
    std::strong_ordering operator<=>(const LargeInt<N> &) const;

    // in- / decrement
    LargeInt<N> &operator++();
    LargeInt<N> &operator--();
    LargeInt<N> operator++(int);
    LargeInt<N> operator--(int);
};

#include "details/member_core.hpp"
#include "operators/all_core.hpp"

#endif //LARGE_INT_CORE_HPP