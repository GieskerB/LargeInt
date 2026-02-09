#ifndef LARGEINT_LARGE_INT_8_HPP
#define LARGEINT_LARGE_INT_8_HPP

#include <compare>
#include <string>
#include <stdexcept>
#include <limits>

#include "details/branch_side.hpp"

/**
 * LargeInts recursive design needs a smallest value to stop at. Choosing N = 8 aka. only a
 * single byte as the smallest value allows to implement every basecase with ease and also
 * make testing easier. Also, this design allows for the use of "small" LargeInts
 * with 16 and 8 bits in contrast to implementing the basecase with a 32-bit Integer.
 */
template<>
class LargeInt<8> {
    template<uint16_t M> friend class LargeInt;
    friend void output_hex(std::ostream&, const LargeInt<8>&, const uint16_t);
    friend uint64_t to_decimal(const LargeInt<8>&);

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

    void initialize_pointers(LargeInt<16> *);
    [[nodiscard]] uint16_t get_msb_index(bool = false) const;

    [[nodiscard]] uint8_t get_upper_bits(uint8_t, branch_side_t, uint16_t) const;
    [[nodiscard]] uint8_t get_lower_bits(uint8_t, branch_side_t, uint16_t) const;

public:
    LargeInt();
    LargeInt(uint8_t);
    LargeInt(const LargeInt<8> &);
    explicit LargeInt (const std::string&);

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
    LargeInt<8> &operator=(const LargeInt<8> &);
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
    LargeInt<8> operator++(int);
    LargeInt<8> operator--(int);

    explicit operator uint64_t() const {
        return m_value;
    }
};

#include "details/large_int_8_impl.ipp"

// =====================================================================================================================

inline LargeInt<8> LargeInt<8>::operator+() const {
    return *this;
}

inline LargeInt<8> LargeInt<8>::operator-() const {
    throw std::runtime_error("Can not invert LargeInt due to being unsigned");
}

inline LargeInt<8> LargeInt<8>::operator+(const LargeInt<8> &other) const {
    LargeInt<8> res{*this};
    res += other;
    return res;
}

inline LargeInt<8> LargeInt<8>::operator-(const LargeInt<8> &other) const {
    LargeInt<8> res{*this};
    res -= other;
    return res;
}

inline LargeInt<16> LargeInt<8>::operator*(const LargeInt<8> &other) const {
    uint16_t mult_res = static_cast<uint16_t>(m_value) * static_cast<uint16_t>(other.m_value);
    LargeInt<16> res;
    res.m_upper.m_value = (mult_res& 0xFF00) >> 8;
    res.m_lower.m_value = mult_res & 0xFF;
    return res;
}

inline LargeInt<8> LargeInt<8>::operator/(const LargeInt<8> &other) const {
    LargeInt<8> res{*this};
    res /= other;
    return res;
}

inline LargeInt<8> LargeInt<8>::operator%(const LargeInt<8> &other) const {
    LargeInt<8> res{*this};
    res %= other;
    return res;
}

inline LargeInt<8> LargeInt<8>::operator~() const {
    LargeInt<8> res{*this};
    res.m_value = ~res.m_value;
    return res;
}
inline LargeInt<8> LargeInt<8>::operator&(const LargeInt<8> & other)const {
    LargeInt<8> res{*this};
    res &= other;
    return res;
}
inline LargeInt<8> LargeInt<8>::operator|(const LargeInt<8> & other)const {
    LargeInt<8> res{*this};
    res |= other;
    return res;
}
inline LargeInt<8> LargeInt<8>::operator^(const LargeInt<8> & other)const {
    LargeInt<8> res{*this};
    res ^= other;
    return res;
}

inline LargeInt<8> LargeInt<8>::operator<<(uint16_t shift) const {
    LargeInt<8> res{*this};
    res <<= shift;
    return res;
}

inline LargeInt<8> LargeInt<8>::operator>>(uint16_t shift) const {
    LargeInt<8> res{*this};
    res >>= shift;
    return res;
}

// =====================================================================================================================

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

inline LargeInt<8> &LargeInt<8>::operator%=(const LargeInt<8> &) {
    // TODO: Division operator implementation!
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

extern LargeInt<32> c;

inline LargeInt<8> &LargeInt<8>::operator<<=(const uint16_t shift) {
    if (shift == 0) return *this;

    const uint8_t shift_mod8 = shift == 0 ? 0 : (shift - 1) % 8 + 1;

    m_value <<= shift;
    // Fill in the missing lower part of the number
    m_value |= p_right == nullptr ? 0 : p_right->get_upper_bits(shift_mod8, branch_side_t::RIGHT, (shift-1) / 8);

    if (shift > 8) {
        // Fill in the missing upper part of the number
        m_value |= p_right == nullptr ? 0 : p_right->get_lower_bits(
            8 - shift_mod8, branch_side_t::RIGHT, (shift-1) / 8 - 1);
    }

    if (p_right != nullptr) *p_right <<= shift;
    return *this;
}

inline LargeInt<8> &LargeInt<8>::operator>>=(const uint16_t shift) {
    const uint8_t shift_mod8 = shift == 0 ? 0 : ((shift - 1) % 8) + 1;

    if (shift == 0) return *this;

    if (shift < 8) {
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

    if (p_right != nullptr) *p_right >>= shift;
    return *this;
}

// =====================================================================================================================

inline bool LargeInt<8>::operator==(const LargeInt<8> &other) const {
    return std::is_eq(m_value <=> other.m_value);
}

inline std::strong_ordering LargeInt<8>::operator<=>(const LargeInt<8> &other) const {
    return m_value <=> other.m_value;
}

// =====================================================================================================================

inline LargeInt<8> &LargeInt<8>::operator++() {
    *this+=1;
    return *this;
}

inline LargeInt<8> &LargeInt<8>::operator--() {
    *this-=1;
    return *this;
}

inline LargeInt<8> LargeInt<8>::operator++(int)  {
    LargeInt<8> res{*this};
    ++*this;
    return res;
}

inline LargeInt<8> LargeInt<8>::operator--(int) {
    LargeInt<8> res{*this};
    --*this;
    return res;
}

// =====================================================================================================================

#endif //LARGEINT_LARGE_INT_8_HPP