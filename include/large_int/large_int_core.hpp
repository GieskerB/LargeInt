#ifndef LARGEINT_LARGE_INT_BASE_HPP
#define LARGEINT_LARGE_INT_BASE_HPP

template<uint16_t N>
class LargeInt {
    template<uint16_t M> friend class LargeInt;
    template<uint16_t M> friend std::ostream& operator<<(std::ostream&, LargeInt<M>&);

    static_assert(N >= 8 , "LargeInt size must be at least one byte in size");
    static_assert((N & (N - 1)) == 0, "LargeInt size must be a power of 2 for recursive splitting");

    LargeInt<N / 2> m_upper, m_lower;
    bool m_overflown, m_underflown;
    const branch_side_t c_branch_side;

    LargeInt<2 * N> *p_parent;

    LargeInt(uint8_t, branch_side_t);
    LargeInt(const LargeInt<N / 2> &);

    void initialize_pointers(LargeInt<2 * N> * = nullptr);

    // [[nodiscard]] uint16_t get_msb_index(bool= true) const;

public:
    LargeInt();
    LargeInt(uint8_t);
    LargeInt(const LargeInt &);
    explicit LargeInt (const std::string&);

    [[nodiscard]] uint16_t get_msb_index(bool= true) const;

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
LargeInt<N>::LargeInt(const std::string &str_repr) : m_upper{0, branch_side_t::LEFT}, m_lower{0, branch_side_t::RIGHT},
                                                     m_overflown{false}, m_underflown{false},
                                                     c_branch_side{branch_side_t::ROOT}, p_parent{nullptr} {
    initialize_pointers();
    static const std::array<LargeInt<N>, 11> constants{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (const char c: str_repr) {
        *this *= constants[10];
        *this += constants[c - '0'];
    }
}

// =====================================================================================================================

#include "operators/arithmetic.hpp"
#include "operators/assignment.hpp"
#include "operators/comparison.hpp"
#include "operators/unary.hpp"

#endif //LARGEINT_LARGE_INT_BASE_HPP