#ifndef LARGE_INT_OPERATORS_8_ASSIGNMENT_HPP
#define LARGE_INT_OPERATORS_8_ASSIGNMENT_HPP

inline LargeInt<8> &LargeInt<8>::operator=(const LargeInt<8> &other) {
    m_value = other.m_value;
    m_overflown = other.m_overflown;
    m_underflown = other.m_underflown;
    const_cast<branch_side_t &>(c_branch_side) = other.c_branch_side;
    p_parent = nullptr;
    p_left = nullptr;
    p_right = nullptr;

    return *this;
}

inline LargeInt<8> &LargeInt<8>::operator+=(const LargeInt<8> &other) {
    // https://stackoverflow.com/questions/199333/how-do-i-detect-unsigned-integer-overflow
    if (other.m_value > 0 && m_value > std::numeric_limits<uint8_t>::max() - other.m_value) {
        // 'm_value + other.m_value' would overflow
        m_overflown = true;
    }
    m_value += other.m_value;
    return *this;
}


inline LargeInt<8> &LargeInt<8>::operator-=(const LargeInt<8> &other) {
    if (other.m_value > 0 && m_value < std::numeric_limits<uint8_t>::min() + other.m_value) {
        // 'm_value - other.m_value' would underflow
        m_underflown = true;
    }
    m_value -= other.m_value;
    return *this;
}


inline LargeInt<8> &LargeInt<8>::operator*=(const LargeInt<8> &other) {
    auto res = *this * other;
    m_value = res.m_lower.m_value;
    return *this;
}

inline LargeInt<8> &LargeInt<8>::operator/=(const LargeInt<8> &other) {
    m_value /= other.m_value;
    return *this;
}

inline LargeInt<8> &LargeInt<8>::operator%=(const LargeInt<8> &other) {
    m_value %= other.m_value;
    return *this;
}

inline LargeInt<8> &LargeInt<8>::operator&=(const LargeInt<8> &other) {
    m_value &= other.m_value;
    return *this;
}

inline LargeInt<8> &LargeInt<8>::operator|=(const LargeInt<8> &other) {
    m_value |= other.m_value;
    return *this;
}

inline LargeInt<8> &LargeInt<8>::operator^=(const LargeInt<8> &other) {
    m_value ^= other.m_value;
    return *this;
}

extern LargeInt<32> c;

inline LargeInt<8> &LargeInt<8>::operator<<=(const uint16_t shift) {
    if (shift == 0) return *this;
    const uint8_t shift_mod8 = shift == 0 ? 0 : (shift - 1) % 8 + 1;

    uint8_t upper_bits, lower_bits;
    if (shift > 8) {
        // Entire m_value gets replaced
        upper_bits = p_right == nullptr ? 0 : p_right->get_lower_bits(shift - 8, branch_side_t::RIGHT) << shift_mod8;
        lower_bits = p_right == nullptr ? 0 : p_right->get_upper_bits(shift, branch_side_t::RIGHT) >> (8 - shift_mod8);
    } else {
        // Only a part gets replaced.
        upper_bits = m_value << shift; // lower #shift bits are zero
        lower_bits = p_right == nullptr ? 0 : p_right->m_value >> (8 - shift); // upper 8-#shift bits are zero
    }
    m_value = upper_bits | lower_bits;

    if (p_right != nullptr) *p_right <<= shift;
    return *this;
}

inline LargeInt<8> &LargeInt<8>::operator>>=(const uint16_t shift) {
    if (shift == 0) return *this;

    const uint8_t shift_mod8 = shift == 0 ? 0 : (shift - 1) % 8 + 1;

    uint8_t upper_bits, lower_bits;
    if (shift > 8) {
        // Entire m_value gets replaced
        lower_bits = p_left == nullptr ? 0 : p_left->get_upper_bits(shift - 8, branch_side_t::LEFT) >> shift_mod8;
        upper_bits = p_left == nullptr ? 0 : p_left->get_lower_bits(shift, branch_side_t::LEFT) << (8 - shift_mod8);
    } else {
        // Only a part gets replaced.
        lower_bits = m_value >> shift; // upper #shift bits are zero
        upper_bits = p_left == nullptr ? 0 : p_left->m_value << (8 - shift); // upper 8-#shift bits are zero
    }
    m_value = upper_bits | lower_bits;

    if (p_left != nullptr) *p_left >>= shift;
    return *this;
}

#endif //LARGE_INT_OPERATORS_8_ASSIGNMENT_HPP
