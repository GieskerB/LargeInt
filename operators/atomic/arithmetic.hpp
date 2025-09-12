//
// Created by bjarn on 19.01.2025.
//

#ifndef LARGEINT_ATOMIC_ARITHMETIC_HPP
#define LARGEINT_ATOMIC_ARITHMETIC_HPP

LargeInt<8> LargeInt<8>::operator+() const {
    LargeInt<8> res{*this};
    res += 1;
    return res;
}

LargeInt<8> LargeInt<8>::operator-() const {
    LargeInt<8> res{*this};
    res -= 1;
    return res;
}

LargeInt<8> LargeInt<8>::operator+(const LargeInt<8> &other) const {
    LargeInt<8> res{*this};
    res += other;
    return res;
}

LargeInt<8> LargeInt<8>::operator-(const LargeInt<8> &other) const {
    LargeInt<8> res{*this};
    res -= other;
    return res;
}

LargeInt<16> LargeInt<8>::operator*(const LargeInt<8> &other) const {
    uint16_t mult_res = static_cast<uint16_t>(m_value) * static_cast<uint16_t>(other.m_value);
    LargeInt<16> res;
    res.m_upper.m_value = mult_res >> 8;
    res.m_lower.m_value = mult_res;
    return res;
}

LargeInt<8> LargeInt<8>::operator/(const LargeInt<8> &other) const {
    LargeInt<8> res{*this};
    res /= other;
    return res;
}

LargeInt<8> LargeInt<8>::operator%(const LargeInt<8> &other) const {
    LargeInt<8> res{*this};
    res %= other;
    return res;
}


LargeInt<8> LargeInt<8>::operator~() const {
    LargeInt<8> res{*this};
    res.m_value = ~res.m_value;
    return res;
}
LargeInt<8> LargeInt<8>::operator&(const LargeInt<8> & other)const {
    LargeInt<8> res{*this};
    res &= other;
    return res;
}
LargeInt<8> LargeInt<8>::operator|(const LargeInt<8> & other)const {
    LargeInt<8> res{*this};
    res |= other;
    return res;
}
LargeInt<8> LargeInt<8>::operator^(const LargeInt<8> & other)const {
    LargeInt<8> res{*this};
    res ^= other;
    return res;
}

LargeInt<8> LargeInt<8>::operator<<(uint16_t shift) const {
    LargeInt<8> res{*this};
    res <<= shift;
    return res;
}

LargeInt<8> LargeInt<8>::operator>>(uint16_t shift) const {
    LargeInt<8> res{*this};
    res >>= shift;
    return res;
}

#endif //LARGEINT_ATOMIC_ARITHMETIC_HPP
