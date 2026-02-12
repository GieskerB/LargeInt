#ifndef LARGEINT_LARGE_INT_8_IMPL_IPP
#define LARGEINT_LARGE_INT_8_IMPL_IPP

#include "../large_int_8.hpp"
#include "../large_int_core.hpp"

#include <array>

// =====================================================================================================================

inline LargeInt<8>::LargeInt() : LargeInt{0} {}


inline LargeInt<8>::LargeInt(uint8_t init_value) : LargeInt(init_value, branch_side_t::ROOT) {}

inline LargeInt<8>::LargeInt(uint8_t init_value, branch_side_t b_side)
        : m_value{init_value}, m_overflown{false}, m_underflown{false}, p_left{nullptr}, p_right{nullptr},
          p_parent{nullptr}, c_branch_side{b_side} {}

inline LargeInt<8>::LargeInt(const LargeInt<8> &copy)
        : m_value{copy.m_value}, m_overflown{false}, m_underflown{false}, p_left{nullptr}, p_right{nullptr},
          p_parent{nullptr}, c_branch_side{copy.c_branch_side} {}

inline LargeInt<8>::LargeInt(const std::string & str_repr) : m_value{0}, m_overflown{false}, m_underflown{false}, p_left{nullptr}, p_right{nullptr},
          p_parent{nullptr}, c_branch_side{branch_side_t::ROOT}{
    for (const char c : str_repr) {
        m_value *= 10;
        m_value += c - '0';
    }
}

// =====================================================================================================================

inline void LargeInt<8>::initialize_pointers(LargeInt<16> *parent, LargeInt<8> ** pp_last_leaf) {

    p_parent = parent;
    if (p_parent != nullptr) {
        if (*pp_last_leaf != nullptr) {
            (*pp_last_leaf)->p_right = this;
        }
        p_left = *pp_last_leaf;
        *pp_last_leaf = this;
    }
}

inline uint16_t LargeInt<8>::get_msb_index(bool init_call) const {
    if (m_value >= 128) return 0;
    if (m_value >= 64) return 1;
    if (m_value >= 32) return 2;
    if (m_value >= 16) return 3;
    if (m_value >= 8) return 4;
    if (m_value >= 4) return 5;
    if (m_value >= 2) return 6;
    if (m_value >= 1) return 7;

    if (p_right == nullptr) return 8;
    return p_right->get_msb_index() + 8;
}


inline uint8_t LargeInt<8>::get_upper_bits(uint8_t num_upper, const branch_side_t direction) const {
    static constexpr std::array<uint8_t, 9> bitmap_lookup{0b00000000,0b10000000, 0b11000000, 0b11100000, 0b11110000,
                                                          0b11111000, 0b11111100, 0b11111110, 0b11111111};

    if (num_upper == 0) return 0;

    if (num_upper < 8 or num_upper == 8 and direction == branch_side_t::RIGHT) {
        if (direction == branch_side_t::LEFT) num_upper = 8 - num_upper;
        return m_value & bitmap_lookup[num_upper];
    }

    if (direction == branch_side_t::RIGHT) {
        return p_right == nullptr ? 0 : p_right->get_upper_bits(num_upper - 8, direction);
    }
    if (direction == branch_side_t::LEFT)  {
        return p_left == nullptr ? 0 : p_left->get_upper_bits(num_upper - 8, direction);
    }
    throw std::runtime_error("Can not determine brother in direction NONE");
}

inline uint8_t LargeInt<8>::get_lower_bits(uint8_t num_lower, const branch_side_t direction) const {
    static constexpr std::array<uint8_t, 9> bitmap_lookup{0b00000000,0b00000001, 0b00000011, 0b00000111, 0b00001111,
                                                          0b00011111, 0b00111111, 0b01111111, 0b11111111};
    if (num_lower == 0) return 0;

    if (num_lower < 8 or num_lower == 8 and direction == branch_side_t::LEFT) {
        if (direction == branch_side_t::RIGHT) num_lower = 8 - num_lower;
        return m_value & bitmap_lookup[num_lower];
    }

    if (direction == branch_side_t::RIGHT) {
        return p_right == nullptr ? 0 : p_right->get_lower_bits(num_lower - 8, direction);
    }
    if (direction == branch_side_t::LEFT)  {
        return p_left == nullptr ? 0 : p_left->get_lower_bits(num_lower - 8, direction);
    }
    throw std::runtime_error("Can not determine brother in direction NONE");

}


inline bool LargeInt<8>::was_overflow() {
    const bool tmp = m_overflown;
    m_overflown = false;
    return tmp;
}

inline bool LargeInt<8>::was_underflow() {
    const bool tmp = m_underflown;
    m_underflown = false;
    return tmp;
}

// =====================================================================================================================


#endif //LARGEINT_LARGE_INT_8_IMPL_IPP