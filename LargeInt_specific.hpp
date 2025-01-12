#ifndef TESTING_LARGEINT_SPECIFIC_HPP
#define TESTING_LARGEINT_SPECIFIC_HPP

#include <cstdint>
#include <stdexcept>
#include <limits>
#include <iostream>
#include <array>
#include <bitset>

#include "LargeInt_general.hpp"

/**
 * Base case Class if user chooses a wrong number of bits.
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


/**
 * Smalles unit, that will be stored is a single byte, 8 bits.
 */
template<>
class LargeInt<8> {
public:
    uint8_t m_value;
    bool m_overflown, m_underflown;
    branch_side_t c_branch_side;

    LargeInt<16> *p_parent;
    LargeInt<8> *p_left, *p_right;


    LargeInt(uint8_t, LargeInt<16> *, branch_side_t);

    static LargeInt<8> *assent(branch_side_t, branch_side_t);

    LargeInt<8> *decent(branch_side_t, bool);

    void initialize_neighbors();

    uint8_t get_upper_bits(uint8_t, branch_side_t, uint16_t) const;

    uint8_t get_lower_bits(uint8_t, branch_side_t, uint16_t) const;

public:
    LargeInt();

    static LargeInt<8> create_instance(uint8_t = 0);

    bool was_overflow();

    bool was_underflow();


    LargeInt operator+(const LargeInt<8> &) const;

    LargeInt &operator+=(const LargeInt<8> &);

    LargeInt operator-(const LargeInt<8> &) const;

    LargeInt &operator-=(const LargeInt<8> &);

    LargeInt<16> operator*(const LargeInt<8> &) const;

    LargeInt<8> &operator*=(const LargeInt<8> &);

    LargeInt operator<<(uint16_t) const;

    LargeInt &operator<<=(uint16_t);

    bool operator==(const LargeInt<8> &) const;

    std::strong_ordering operator<=>(const LargeInt<8> &) const;

};

/*
 * +------------+
 * |Constructors|
 * +------------+
 */

LargeInt<8>::LargeInt() : LargeInt{0, nullptr, branch_side_t::NONE} {}

LargeInt<8>::LargeInt(uint8_t init_value, LargeInt<16> *parent_ptr, branch_side_t b_side)
        : m_value{init_value}, m_overflown{false}, m_underflown{false}, p_left{nullptr}, p_right{nullptr},
          p_parent{parent_ptr}, c_branch_side{b_side} {}

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

void LargeInt<8>::initialize_neighbors() {
    if (p_parent != nullptr) {
        p_left = p_parent->get_brother(c_branch_side, branch_side_t::LEFT);
        p_right = p_parent->get_brother(c_branch_side, branch_side_t::RIGHT);
    }
}


uint8_t LargeInt<8>::get_upper_bits(uint8_t num_upper, branch_side_t direction, uint16_t total_steps) const {
    static constexpr std::array<uint8_t, 8> bitmap_lookup{0b10000000, 0b11000000, 0b11100000, 0b11110000,
                                                          0b11111000, 0b11111100, 0b11111110, 0b11111111};

    if (direction == branch_side_t::NONE) {
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

    if (direction == branch_side_t::NONE) {
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
 * +-----------------------------+
 * |Static methods implementation|
 * +-----------------------------+
 */

LargeInt<8> LargeInt<8>::create_instance(uint8_t init_value) {
    LargeInt<8> instance{init_value, nullptr, branch_side_t::NONE};
    instance.initialize_neighbors();
    return instance;
}

/*
 * +-----------------------+
 * |Operator implementation|
 * +-----------------------+
 */

LargeInt<8> LargeInt<8>::operator+(const LargeInt<8> &other) const {
    LargeInt<8> res{*this};
    res += other;
    return res;
}

LargeInt<8> &LargeInt<8>::operator+=(const LargeInt<8> &other) {
    /*
     * https://stackoverflow.com/questions/199333/how-do-i-detect-unsigned-integer-overflow
     */
    if (other.m_value > 0 && m_value > std::numeric_limits<uint8_t>::max() - other.m_value) {
        // `m_value + other.m_value` would overflow
        m_overflown = true;
    }
    m_value += other.m_value;

    return *this;
}

LargeInt<8> LargeInt<8>::operator-(const LargeInt<8> &other) const {
    LargeInt<8> res{*this};
    res -= other;
    return res;
}

LargeInt<8> &LargeInt<8>::operator-=(const LargeInt<8> &other) {
    if (other.m_value > 0 && m_value < std::numeric_limits<uint8_t>::min() + other.m_value) {
        // `m_value - other.m_value` would underflow
        m_underflown = true;
    }
    m_value -= other.m_value;

    return *this;
}

LargeInt<16> LargeInt<8>::operator*(const LargeInt<8> &other) const {
    uint16_t mult_res = static_cast<uint16_t>(m_value) * static_cast<uint16_t>(other.m_value);
    LargeInt<16> res;
    res.m_upper.m_value = mult_res >> 8;
    res.m_lower.m_value = mult_res;
    return res;
}

LargeInt<8> &LargeInt<8>::operator*=(const LargeInt<8> &other) {
    auto res = *this * other;
    m_value = res.m_lower.m_value;
    return *this;
}

LargeInt<8> LargeInt<8>::operator<<(uint16_t shift) const {
    LargeInt<8> res{*this};
    res <<= shift;
    return res;
}

LargeInt<8> &LargeInt<8>::operator<<=(uint16_t shift) {
    const uint8_t shift_mod8 = shift == 0 ? 0 : ((shift - 1) % 8) + 1;

    if (shift == 0) {
        return *this;
    } else if (shift < 8) {
        m_value <<= shift;
        m_value |= p_right == nullptr ? 0 : p_right->get_upper_bits(shift_mod8, branch_side_t::RIGHT, 0);;
    } else if (shift_mod8 == 8) {
        m_value = p_right == nullptr ? 0 : p_right->get_upper_bits(shift_mod8, branch_side_t::RIGHT, shift / 8 - 1);
    } else {
        m_value = 0;
        m_value |=
                p_right == nullptr ? 0 : p_right->get_lower_bits(8 - shift_mod8, branch_side_t::RIGHT, shift / 8 - 1);
        m_value |= p_right == nullptr ? 0 : p_right->get_upper_bits(shift_mod8, branch_side_t::RIGHT, shift / 8);
    }

    if (p_right != nullptr) {
        *p_right <<= shift;
    }

    return *this;
}

bool LargeInt<8>::operator==(const LargeInt<8> &other) const {
    return std::is_eq(m_value <=> other.m_value);
}

std::strong_ordering LargeInt<8>::operator<=>(const LargeInt<8> &other) const {
    return m_value <=> other.m_value;
}

#endif //TESTING_LARGEINT_SPECIFIC_HPP
