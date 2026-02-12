#ifndef LARGEINT_GENERAL_ASSIGNMENT_HPP
#define LARGEINT_GENERAL_ASSIGNMENT_HPP

// TODO 11

template<uint16_t N>
LargeInt<N> &LargeInt<N>::operator=(const LargeInt<N> &copy) {
    if (&copy == this) {
        return *this;
    }
    m_upper = copy.m_upper;
    m_lower = copy.m_lower;
    m_overflown = copy.m_overflown;
    m_underflown = copy.m_underflown;
    const_cast<branch_side_t &>(c_branch_side) = copy.c_branch_side;
    initialize_pointers(nullptr);
    return *this;
}


template<uint16_t N>
LargeInt<N> &LargeInt<N>::operator+=(const LargeInt<N> &other) {
    m_lower += other.m_lower;
    m_upper += other.m_upper;

    if (m_lower.was_overflow()) {
        ++m_upper;
    }
    m_overflown = m_upper.was_overflow();

    return *this;
}


template<uint16_t N>
LargeInt<N> &LargeInt<N>::operator-=(const LargeInt<N> &other) {
    m_lower -= other.m_lower;
    m_upper -= other.m_upper;

    if (m_lower.was_underflow()) {
        --m_upper;
    }
    m_underflown = m_upper.was_underflow();

    return *this;
}


template<uint16_t N>
LargeInt<N> &LargeInt<N>::operator*=(const LargeInt<N> &other) {
    *this = (*this * other).m_lower;
    return *this;
}

template<uint16_t N>
std::pair<LargeInt<N>, LargeInt<N>>
div_three_halves_by_two(const LargeInt<N / 4> &a1, const LargeInt<N / 4> &a2, const LargeInt<N / 4> &a3,
                        const LargeInt<N / 4> &b1, const LargeInt<N / 4> &b2) {

    LargeInt<N> A{a1, a2};
    LargeInt<N> B{b1, b2};
    auto q = A / b1;
    auto c = A - q * b1;
    auto D = q * b2;
    auto R = LargeInt<N>{c, a3} - D;
    if (R < 0) { // q is too large by at least one
        --q;
        R += B;
        if (R < 0) { // q is still too large
            --q;
            R += B;
        }
    }

    return {q, R};
}

template<uint16_t N>
std::pair<LargeInt<N>, LargeInt<N>>
div_two_digits_by_one(const LargeInt<N / 2> &a_high, const LargeInt<N / 2> &a_low, const LargeInt<N / 2> &b) {
    LargeInt<N / 4> a1 = a_high.m_upper;
    LargeInt<N / 4> a2 = a_high.m_lower;
    LargeInt<N / 4> a3 = a_low.m_upper;
    LargeInt<N / 4> a4 = a_low.m_lower;
    LargeInt<N / 4> b1 = b.m_upper;
    LargeInt<N / 4> b2 = b.m_lower;

    auto q1_R = div_three_halves_by_two(a1, a2, a3, b1, b2);

    LargeInt<N / 2> r1 = q1_R.second.m_upper;
    LargeInt<N / 2> r2 = q1_R.second.m_lower;

    auto q2_S = DivThreeHalvesByTwo(r1, r2, a4, b1, b2);

    LargeInt<N> Q{q1_R.first, q2_S.first};

    return {Q, q2_S.second};
}



template<uint16_t N>
LargeInt<N> &LargeInt<N>::operator/=(const LargeInt<N> &other) {
    // TODO Division: Burnikel-Ziegler Algorithm
    // https://pure.mpg.de/rest/items/item_1819444_4/component/file_2599480/content

    auto Q_S = div_two_digits_by_one<N>(this->m_upper, this->m_lower, other.m_lower);
    this->m_upper = Q_S.first.m_upper;
    this->m_lower = Q_S.first.m_lower;
    this->initialize_pointers(nullptr);
    return *this;
}

template<uint16_t N>
LargeInt<N> &LargeInt<N>::operator%=(const LargeInt<N> &other) {
    auto Q_S = div_two_digits_by_one(this->m_upper, this->m_lower, other.m_lower);
    this->m_upper = Q_S.second.m_upper;
    this->m_lower = Q_S.second.m_lower;
    this->initialize_pointers(nullptr);
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


#endif //LARGEINT_GENERAL_ASSIGNMENT_HPP
