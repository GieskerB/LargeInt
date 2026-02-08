#ifndef TESTING_LARGEINT_GENERAL_HPP
#define TESTING_LARGEINT_GENERAL_HPP

#include <cstdint>
#include <stdexcept>
#include <limits>
#include <iostream>


// =====================================================================================================================


enum class branch_side_t : int8_t {
    LEFT = -1, RIGHT = 1, ROOT = 0
};


// =====================================================================================================================


template<uint16_t N>
class LargeInt;

template<>
class LargeInt<8>;


// =====================================================================================================================


template<uint16_t N>
class LargeInt {

    template<uint16_t M>
    friend class LargeInt;

    friend std::ostream &operator<<(std::ostream &os, const LargeInt<8>& large_int);
    friend std::ostream &operator<<(std::ostream &os, const LargeInt<16>& large_int);
    friend std::ostream &operator<<(std::ostream &os, const LargeInt<32>& large_int);
    friend std::ostream &operator<<(std::ostream &os, const LargeInt<64>& large_int);

    LargeInt<N / 2> m_upper, m_lower;
    bool m_overflown, m_underflown;
    const branch_side_t c_branch_side;

    LargeInt<2 * N> *p_parent;

    LargeInt(uint8_t, branch_side_t);
    LargeInt(const LargeInt<N / 2> &);
    LargeInt(const LargeInt<N / 2> &,const LargeInt<N / 2> &);
    LargeInt<8> *assent(branch_side_t, branch_side_t);
    LargeInt<8> *decent(branch_side_t, bool);
    void initialize_pointers(LargeInt<2 * N> * = nullptr);

public:
    LargeInt();
    LargeInt(uint8_t);
    LargeInt(const LargeInt &);

    LargeInt<8> *get_brother(branch_side_t, branch_side_t);
    bool was_overflow();
    bool was_underflow();

    //arithmetic
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
    LargeInt<N> &operator=(const LargeInt<N> &);
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
    LargeInt<N> operator++();
    LargeInt<N> operator--();
    LargeInt<N> &operator++(int);
    LargeInt<N> &operator--(int);
};

/*
 * +------------+
 * |Constructors|
 * +------------+
 */


template<uint16_t N>
LargeInt<N>::LargeInt() : LargeInt<N>{0} {
}


template<uint16_t N>
LargeInt<N>::LargeInt(uint8_t init_value): LargeInt<N>{init_value, branch_side_t::ROOT} {};

template<uint16_t N>
LargeInt<N>::LargeInt(uint8_t init_value, enum branch_side_t b_side)
        :  m_upper{0, branch_side_t::LEFT}, m_lower{init_value, branch_side_t::RIGHT}, m_overflown{false},
           m_underflown{false}, c_branch_side{b_side}, p_parent{nullptr} {
    if ((N & (N - 1)) != 0) {
        //Not a perfect power of 2!
        throw std::runtime_error("LargeInt in only supports a perfect power of 2 number of Bits.");
    }

    if (c_branch_side == branch_side_t::ROOT) {
        initialize_pointers();
    }

}

template<uint16_t N>
LargeInt<N>::LargeInt(const LargeInt<N> &copy): m_upper{copy.m_upper}, m_lower{copy.m_lower}, m_overflown{false},
                                                m_underflown{false}, c_branch_side{copy.c_branch_side},
                                                p_parent{nullptr} {
    if (c_branch_side == branch_side_t::ROOT) {
        initialize_pointers();
    }
}

template<uint16_t N>
LargeInt<N>::LargeInt(const LargeInt<N / 2> &lower):  m_upper{0, branch_side_t::LEFT}, m_lower{lower},
                                                m_overflown{false},
                                                m_underflown{false}, c_branch_side{branch_side_t::ROOT},
                                                p_parent{nullptr} {
    initialize_pointers(nullptr);
}

template<uint16_t N>
LargeInt<N>::LargeInt(const LargeInt<N / 2> &upper,const LargeInt<N / 2> &lower):  m_upper{upper}, m_lower{lower},
                                                      m_overflown{false},
                                                      m_underflown{false}, c_branch_side{branch_side_t::ROOT},
                                                      p_parent{nullptr} {
    initialize_pointers(nullptr);
}

/*
 * +----------------------+
 * |Methods implementation|
 * +----------------------+
 */

template<uint16_t N>
LargeInt<8> *LargeInt<N>::assent(branch_side_t coming, branch_side_t heading) {
    if (coming == branch_side_t::LEFT and heading == branch_side_t::RIGHT) {
        return m_lower.decent(branch_side_t::ROOT, true);
    } else if (coming == branch_side_t::RIGHT and heading == branch_side_t::LEFT) {
        return m_upper.decent(branch_side_t::ROOT, true);
    }
    if (p_parent == nullptr) {
        return nullptr;
    }
    return p_parent->assent(c_branch_side, heading);
}

template<uint16_t N>
LargeInt<8> *LargeInt<N>::decent(branch_side_t direction, bool is_first_decent) {

    if (is_first_decent) {
        if (direction == branch_side_t::LEFT) {
            return m_upper.decent(branch_side_t::RIGHT, false);
        } else {
            return m_lower.decent(branch_side_t::LEFT, false);
        }
    }
    if (direction == branch_side_t::LEFT) {
        return m_upper.decent(direction, false);
    } else {
        return m_lower.decent(direction, false);
    }

}

template<uint16_t N>
void LargeInt<N>::initialize_pointers(LargeInt<2 * N> *parent) {
    p_parent = parent;
    m_upper.initialize_pointers(this);
    m_lower.initialize_pointers(this);
}

template<uint16_t N>
LargeInt<8> *LargeInt<N>::get_brother(branch_side_t coming, branch_side_t heading) {
    if (coming == branch_side_t::ROOT or heading == branch_side_t::ROOT) {
        throw std::runtime_error("Can not find brother of node if either coming or heading from NONE!");
    }
    return assent(coming, heading);
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

/*
 * +-----------------------+
 * |Operator implementation|
 * +-----------------------+
 */

#include "operators/general/arithmetic.hpp"
#include "operators/general/assignment.hpp"
#include "operators/general/comparison.hpp"
#include "operators/general/in-de-crement.hpp"


#endif //TESTING_LARGEINT_GENERAL_HPP
