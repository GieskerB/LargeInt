//
// Created by bjarn on 19.01.2025.
//

#ifndef LARGEINT_ATOMIC_ASSIGNMENT_HPP
#define LARGEINT_ATOMIC_ASSIGNMENT_HPP

inline LargeInt<8> &LargeInt<8>::operator=(const LargeInt<8> &copy) {
    m_value = copy.m_value;
    m_overflown = copy.m_overflown;
    m_underflown = copy.m_underflown;
    const_cast<branch_side_t &>(c_branch_side) = copy.c_branch_side;
    p_parent = nullptr;
    p_left = nullptr;
    p_right = nullptr;

    return *this;
}

inline LargeInt<8> &LargeInt<8>::operator+=(const LargeInt<8> &other) {
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


inline LargeInt<8> &LargeInt<8>::operator-=(const LargeInt<8> &other) {
    if (other.m_value > 0 && m_value < std::numeric_limits<uint8_t>::min() + other.m_value) {
        // `m_value - other.m_value` would underflow
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

// TODO see other header

inline LargeInt<8> &LargeInt<8>::operator/=(const LargeInt<8> &other) {
    m_value /= other.m_value;
    return *this;
}


inline LargeInt<8> &LargeInt<8>::operator<<=(uint16_t shift) {
    const uint8_t shift_mod8 = shift == 0 ? 0 : ((shift - 1) % 8) + 1;

    if (shift == 0) return *this;

    if (shift < 8) {
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


inline LargeInt<8> &LargeInt<8>::operator%=(const LargeInt<8> &) {
    // TODO
    throw std::runtime_error("not implemented");
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

inline LargeInt<8> &LargeInt<8>::operator>>=(uint16_t shift) {
    const uint8_t shift_mod8 = shift == 0 ? 0 : ((shift - 1) % 8) + 1;

    if (shift == 0) {
        return *this;
    } else if (shift < 8) {
        m_value >>= shift;
        m_value |= p_right == nullptr ? 0 : p_right->get_lower_bits(shift_mod8, branch_side_t::LEFT, 0);;
    } else if (shift_mod8 == 8) {
        m_value = p_right == nullptr ? 0 : p_right->get_lower_bits(shift_mod8, branch_side_t::LEFT, shift / 8 - 1);
    } else {
        m_value = 0;
        m_value |=
                p_right == nullptr ? 0 : p_right->get_upper_bits(8 - shift_mod8, branch_side_t::LEFT, shift / 8 - 1);
        m_value |= p_right == nullptr ? 0 : p_right->get_lower_bits(shift_mod8, branch_side_t::LEFT, shift / 8);
    }

    if (p_right != nullptr) {
        *p_right >>= shift;
    }

    return *this;
}

#endif //LARGEINT_ATOMIC_ASSIGNMENT_HPP
