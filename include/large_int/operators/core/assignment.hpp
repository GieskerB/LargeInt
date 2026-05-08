#ifndef LARGE_INT_OPERATORS_CORE_ASSIGNMENT_HPP
#define LARGE_INT_OPERATORS_CORE_ASSIGNMENT_HPP

template<uint16_t N>
LargeInt<N> &LargeInt<N>::operator=(const LargeInt<N> &other) {
    if (&other == this) {
        return *this;
    }
    m_upper = other.m_upper;
    m_lower = other.m_lower;
    m_overflown = other.m_overflown;
    m_underflown = other.m_underflown;
    const_cast<branch_side_t &>(c_branch_side) = other.c_branch_side;
    initialize_pointers(nullptr);
    return *this;
}

template<uint16_t N>
LargeInt<N> &LargeInt<N>::operator+=(const LargeInt<N> &other) {
    m_lower += other.m_lower;
    m_upper += other.m_upper;

    // Check if upper overflowed the first time after the +=
    m_overflown = m_upper.was_overflow();
    if (m_lower.was_overflow()) {
        ++m_upper;
    }
    // Check if upper overflowed a second time after the ++
    m_overflown |= m_upper.was_overflow();

    return *this;
}

template<uint16_t N>
LargeInt<N> &LargeInt<N>::operator-=(const LargeInt<N> &other) {
    m_lower -= other.m_lower;
    m_upper -= other.m_upper;

    // Check if upper underflowed the first time after the -=
    m_underflown = m_upper.was_underflow();
    if (m_lower.was_underflow()) {
        --m_upper;
    }
    // Check if upper underflowed a second time after the --
    m_underflown |= m_upper.was_underflow();

    return *this;
}

template<uint16_t N>
LargeInt<N> &LargeInt<N>::operator*=(const LargeInt<N> &other) {
    *this = (*this * other).m_lower;
    return *this;
}

template<uint16_t N>
LargeInt<N> &LargeInt<N>::operator/=(const LargeInt<N> &other) {
    *this = *this / other;
    return *this;
}

template<uint16_t N>
LargeInt<N> &LargeInt<N>::operator%=(const LargeInt<N> &other) {
    *this = *this % other;
    return *this;
}

template<uint16_t N>
LargeInt<N> &LargeInt<N>::operator&=(const LargeInt<N> &other) {
    m_upper &= other.m_upper;
    m_lower &= other.m_lower;
    return *this;
}

template<uint16_t N>
LargeInt<N> &LargeInt<N>::operator|=(const LargeInt<N> &other) {
    m_upper |= other.m_upper;
    m_lower |= other.m_lower;
    return *this;
}

template<uint16_t N>
LargeInt<N> &LargeInt<N>::operator^=(const LargeInt<N> &other) {
    m_upper ^= other.m_upper;
    m_lower ^= other.m_lower;
    return *this;
}


template<uint16_t N>
LargeInt<N> &LargeInt<N>::operator<<=(uint16_t shift) {
    m_upper <<= shift;
    return *this;
}


template<uint16_t N>
LargeInt<N> &LargeInt<N>::operator>>=(uint16_t shift) {
    m_lower >>= shift;
    return *this;
}


#endif //LARGE_INT_OPERATORS_CORE_ASSIGNMENT_HPP
