#ifndef LARGEINT_LARGE_INT_BASE_HPP
#define LARGEINT_LARGE_INT_BASE_HPP

template<uint16_t N>
class LargeInt {
    template<uint16_t M> friend class LargeInt;
    friend uint64_t to_decimal(const LargeInt<16>&);
    friend uint64_t to_decimal(const LargeInt<32>&);
    friend uint64_t to_decimal(const LargeInt<64>&);
    template<uint16_t M> friend void output_hex(std::ostream& os, const LargeInt<M>& number, uint16_t base) ;
    template<uint16_t M> friend void output_bin(std::ostream& os, const LargeInt<M>& number, uint16_t base) ;

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
    LargeInt<N> operator+() const;
    LargeInt<N> operator-() const;
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

// =====================================================================================================================

template<uint16_t N>
LargeInt<N>::LargeInt() : LargeInt<N>{0} {
}

template<uint16_t N>
LargeInt<N>::LargeInt(uint8_t init_value) : LargeInt<N>{init_value, branch_side_t::ROOT} {
}

template<uint16_t N>
LargeInt<N>::LargeInt(uint8_t init_value, enum branch_side_t b_side) : m_upper{0, branch_side_t::LEFT},
                                                                       m_lower{init_value, branch_side_t::RIGHT},
                                                                       m_overflown{false}, m_underflown{false},
                                                                       c_branch_side{b_side}, p_parent{nullptr} {
    if (c_branch_side == branch_side_t::ROOT) {
        initialize_pointers();
    }
}

template<uint16_t N>
LargeInt<N>::LargeInt(const LargeInt<N> &copy) : m_upper{copy.m_upper}, m_lower{copy.m_lower}, m_overflown{false},
                                                 m_underflown{false}, c_branch_side{copy.c_branch_side},
                                                 p_parent{nullptr} {
    if (c_branch_side == branch_side_t::ROOT) {
        initialize_pointers();
    }
}

template<uint16_t N>
LargeInt<N>::LargeInt(const LargeInt<N / 2> &lower) : m_upper{0, branch_side_t::LEFT}, m_lower{lower},
                                                      m_overflown{false}, m_underflown{false},
                                                      c_branch_side{branch_side_t::ROOT}, p_parent{nullptr} {
    initialize_pointers();
}

template<uint16_t N>
LargeInt<N>::LargeInt(const LargeInt<N / 2> &upper,int) : m_upper{upper}, m_lower{0,branch_side_t::RIGHT},
                                                      m_overflown{false}, m_underflown{false},
                                                      c_branch_side{branch_side_t::ROOT}, p_parent{nullptr} {
    initialize_pointers();
}

template<uint16_t N>
LargeInt<N>::LargeInt(const LargeInt<N / 2> &upper,const LargeInt<N / 2> &lower) : m_upper{upper}, m_lower{lower},
                                                      m_overflown{false}, m_underflown{false},
                                                      c_branch_side{branch_side_t::ROOT}, p_parent{nullptr} {
    initialize_pointers();
}

template<uint16_t N>
LargeInt<N>::LargeInt(const std::string &str_repr) : m_upper{0, branch_side_t::LEFT}, m_lower{0, branch_side_t::RIGHT},
                                                     m_overflown{false}, m_underflown{false},
                                                     c_branch_side{branch_side_t::ROOT}, p_parent{nullptr} {
    initialize_pointers();

    for (const char c: str_repr) {
        this->multiply_by_ten(c - '0');
    }
}

// =====================================================================================================================

// inline thread_local LargeInt<8>* p_last_leaf = nullptr;

template<uint16_t N>
void LargeInt<N>::initialize_pointers(LargeInt<2 * N> *parent, LargeInt<8>** pp_last_leaf) {
    p_parent = parent;
    if (pp_last_leaf == nullptr) {
        LargeInt<8> *p_last_leaf = nullptr;
        m_upper.initialize_pointers(this, &p_last_leaf);
        m_lower.initialize_pointers(this, &p_last_leaf);
    } else {
        m_upper.initialize_pointers(this, pp_last_leaf);
        m_lower.initialize_pointers(this, pp_last_leaf);
    }
}

template<uint16_t N>
void LargeInt<N>::multiply_by_ten(uint8_t carry) {
    m_lower.multiply_by_ten(carry);
}

template<uint16_t N>
bool LargeInt<N>::was_overflow() {
    const bool tmp = m_overflown;
    m_overflown = false;
    return tmp;
}

template<uint16_t N>
bool LargeInt<N>::was_underflow() {
    const bool tmp = m_underflown;
    m_underflown = false;
    return tmp;
}

// =====================================================================================================================

#include "operators/arithmetic.hpp"
#include "operators/assignment.hpp"
#include "operators/comparison.hpp"
#include "operators/unary.hpp"

#endif //LARGEINT_LARGE_INT_BASE_HPP