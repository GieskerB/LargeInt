#ifndef TESTING_LARGEINT_SPECIFIC_HPP
#define TESTING_LARGEINT_SPECIFIC_HPP

#include <cstdint>
#include <stdexcept>
#include <limits>
#include <iostream>
#include <array>
#include <bitset>

#include "LargeInt_general.hpp"

/*
 * Will only throw exceptions, when used. Necessary for compiler statisfaction with recursive design.
 */
template<>
class LargeInt<0> {
public:
    LargeInt();
};

LargeInt<0>::LargeInt() {
    throw std::runtime_error("LargeInt in only supports a perfect power of 2 number of Bits.");
}

/*
 * Will only throw exceptions, when used. Necessary for compiler statisfaction with recursive design.
 */
template<>
class LargeInt<1 << 15> {
public:
    static LargeInt<8> *assent(branch_side_t, branch_side_t);

    static LargeInt<8> *decent(branch_side_t, bool);

    LargeInt();
};

LargeInt<1 << 15>::LargeInt() {
    throw std::runtime_error("Capacity limit of LargeInt reached. Only < (2^15) Bits allowed");
}

LargeInt<8> *LargeInt<1 << 15>::assent(branch_side_t, branch_side_t) {
    throw std::runtime_error("Capacity limit of LargeInt reached. Only < (2^15) Bits allowed");
}

LargeInt<8> *LargeInt<1 << 15>::decent(branch_side_t, bool) {
    throw std::runtime_error("Capacity limit of LargeInt reached. Only < (2^15) Bits allowed");
}


// =====================================================================================================================


template<uint16_t N>
class LargeInt;


// =====================================================================================================================


/**
 * LargeInts recursive design needs a smallest value to stop at. Choosing N = 8 aka. only a
 * single byte as the smallest value allows to implement every basecase with ease and also
 * make testing easier. Also this design allows for the use of "small" LargeInts
 * with 16 and 8 bits in contrast to implementing the basecase with a 32-bit Integer.
 */
template<>
class LargeInt<8> {

    template<uint16_t M>
    friend
    class LargeInt;

    friend std::ostream &operator<<(std::ostream &os, const LargeInt<8> &large_int);
    friend std::ostream &operator<<(std::ostream &os, const LargeInt<16> &large_int);
    friend std::ostream &operator<<(std::ostream &os, const LargeInt<32> &large_int);
    friend std::ostream &operator<<(std::ostream &os, const LargeInt<64> &large_int);

    /// Stores one single byte of the possibly huge LargeInt instance.
    uint8_t m_value;
    /// Temporal values used to make addition and subtraction easier.
    bool m_overflown, m_underflown;
    /// Remembers if instance is the upper or lower part of parent instance.
    const branch_side_t c_branch_side;

    /// For easier traversal in huge LargeInts, an instance stores a pointer to its parent
    LargeInt<16> *p_parent;
    /// For easier traversal only the LargeInt<8> knows its left and right brother
    LargeInt<8> *p_left, *p_right;

    LargeInt(uint8_t, branch_side_t);

    static LargeInt<8> *assent(branch_side_t, branch_side_t);
    LargeInt<8> *decent(branch_side_t, bool);
    void initialize_pointers(LargeInt<16> *);
    [[nodiscard]] uint8_t get_upper_bits(uint8_t, branch_side_t, uint16_t) const;
    [[nodiscard]] uint8_t get_lower_bits(uint8_t, branch_side_t, uint16_t) const;

public:
    LargeInt();
    LargeInt(uint8_t);
    LargeInt(const LargeInt<8> &);

    bool was_overflow();
    bool was_underflow();

    // arithmetic
    LargeInt<8> operator+() const;
    LargeInt<8> operator-() const;
    LargeInt<8> operator+(const LargeInt<8> &) const;
    LargeInt<8> operator-(const LargeInt<8> &) const;
    LargeInt<16> operator*(const LargeInt<8> &) const;
    LargeInt<8> operator/(const LargeInt<8> &) const;
    LargeInt<8> operator%(const LargeInt<8> &) const;
    LargeInt<8> operator~() const;
    LargeInt<8> operator&(const LargeInt<8> &) const;
    LargeInt<8> operator|(const LargeInt<8> &) const;
    LargeInt<8> operator^(const LargeInt<8> &) const;
    LargeInt<8> operator<<(uint16_t) const;
    LargeInt<8> operator>>(uint16_t) const;

    // assignment
    LargeInt<8> &operator=(const LargeInt &);
    LargeInt<8> &operator+=(const LargeInt<8> &);
    LargeInt<8> &operator-=(const LargeInt<8> &);
    LargeInt<8> &operator*=(const LargeInt<8> &);
    LargeInt<8> &operator/=(const LargeInt<8> &);
    LargeInt<8> &operator%=(const LargeInt<8> &);
    LargeInt<8> &operator&=(const LargeInt<8> &);
    LargeInt<8> &operator|=(const LargeInt<8> &);
    LargeInt<8> &operator^=(const LargeInt<8> &);
    LargeInt<8> &operator<<=(uint16_t);
    LargeInt<8> &operator>>=(uint16_t);

    // comparison
    bool operator==(const LargeInt<8> &) const;
    std::strong_ordering operator<=>(const LargeInt<8> &) const;

    // in- / decrement
    LargeInt<8> &operator++();
    LargeInt<8> &operator--();
    LargeInt<8> &operator++(int);
    LargeInt<8> &operator--(int);


};

/*
 * +------------+
 * |Constructors|
 * +------------+
 */

LargeInt<8>::LargeInt() : LargeInt{0} {}


LargeInt<8>::LargeInt(uint8_t init_value) : LargeInt(init_value, branch_side_t::ROOT) {}

LargeInt<8>::LargeInt(uint8_t init_value, branch_side_t b_side)
        : m_value{init_value}, m_overflown{false}, m_underflown{false}, p_left{nullptr}, p_right{nullptr},
          p_parent{nullptr}, c_branch_side{b_side} {}

// TODO p_left, p_right
LargeInt<8>::LargeInt(const LargeInt<8> &copy)
        : m_value{copy.m_value}, m_overflown{false}, m_underflown{false}, p_left{nullptr}, p_right{nullptr},
          p_parent{nullptr}, c_branch_side{copy.c_branch_side} {}


/*
 * +----------------------+
 * |Methods implementation|
 * +----------------------+
 */

LargeInt<8> *LargeInt<8>::assent(branch_side_t, branch_side_t) {
    throw std::logic_error("Function not implemented!");
}

LargeInt<8> *LargeInt<8>::decent(branch_side_t, bool) {
    return this;
}

void LargeInt<8>::initialize_pointers(LargeInt<16> *parent) {
    p_parent = parent;
    if (p_parent != nullptr) {
        p_left = p_parent->get_brother(c_branch_side, branch_side_t::LEFT);
        p_right = p_parent->get_brother(c_branch_side, branch_side_t::RIGHT);
    }
}


uint8_t LargeInt<8>::get_upper_bits(uint8_t num_upper, branch_side_t direction, uint16_t total_steps) const {
    static constexpr std::array<uint8_t, 8> bitmap_lookup{0b10000000, 0b11000000, 0b11100000, 0b11110000,
                                                          0b11111000, 0b11111100, 0b11111110, 0b11111111};

    if (direction == branch_side_t::ROOT) {
        throw std::runtime_error("Can not determine brother in direction NONE");
    }

    if (total_steps == 0) {
        return (m_value & bitmap_lookup[num_upper - 1]) >> (8 - num_upper);
    }

    if (direction == branch_side_t::RIGHT) {
        if (p_right == nullptr) return 0;
        return p_right->get_upper_bits(num_upper, direction, total_steps - 1);
    } else {
        if (p_left == nullptr) return 0;
        return p_left->get_upper_bits(num_upper, direction, total_steps - 1);
    }
}

uint8_t LargeInt<8>::get_lower_bits(uint8_t num_upper, branch_side_t direction, uint16_t total_steps) const {
    static constexpr std::array<uint8_t, 8> bitmap_lookup{0b00000001, 0b00000011, 0b00000111, 0b00001111,
                                                          0b00011111, 0b00111111, 0b01111111, 0b11111111};

    if (direction == branch_side_t::ROOT) {
        throw std::runtime_error("Can not determine brother in direction NONE");
    }

    if (total_steps == 0) {
        return m_value & bitmap_lookup[num_upper - 1] << (8 - num_upper);
    }
    if (direction == branch_side_t::RIGHT) {
        if (p_right == nullptr) return 0;
        return p_right->get_lower_bits(num_upper, direction, total_steps - 1);
    } else {
        if (p_left == nullptr) return 0;
        return p_left->get_lower_bits(num_upper, direction, total_steps - 1);
    }
}


bool LargeInt<8>::was_overflow() {
    const bool tmp = m_overflown;
    m_overflown = false;
    return tmp;
}

bool LargeInt<8>::was_underflow() {
    const bool tmp = m_underflown;
    m_underflown = false;
    return tmp;
}

/*
 * +-----------------------+
 * |Operator implementation|
 * +-----------------------+
 */

#include "operators/specific/arithmetic.hpp"
#include "operators/specific/assignment.hpp"
#include "operators/specific/comparison.hpp"
#include "operators/specific/in-de-crement.hpp"


#endif //TESTING_LARGEINT_SPECIFIC_HPP
