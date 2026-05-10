#ifndef LARGE_INT_DETAILS_MEMBER_CORE_HPP
#define LARGE_INT_DETAILS_MEMBER_CORE_HPP

/** @file member_core.hpp */

template<uint16_t N>
LargeInt<N>::LargeInt() : LargeInt<N>{0} {
}

template<uint16_t N>
LargeInt<N>::LargeInt(uint8_t init_value) : LargeInt<N>{init_value, branch_side_t::ROOT} {
}

template<uint16_t N>
LargeInt<N>::LargeInt(uint8_t init_value, enum branch_side_t b_side) : m_upper{0, branch_side_t::LEFT},
                                                                       m_lower{init_value, branch_side_t::RIGHT},
                                                                       m_overflown{false}, m_underflown{false},
                                                                       c_branch_side{b_side}, p_parent{nullptr} {
    if (c_branch_side == branch_side_t::ROOT) {
        initialize_pointers();
    }
}

template<uint16_t N>
LargeInt<N>::LargeInt(const LargeInt<N> &copy) : m_upper{copy.m_upper}, m_lower{copy.m_lower}, m_overflown{false},
                                                 m_underflown{false}, c_branch_side{copy.c_branch_side},
                                                 p_parent{nullptr} {
    if (c_branch_side == branch_side_t::ROOT) {
        initialize_pointers();
    }
}

template<uint16_t N>
LargeInt<N>::LargeInt(const LargeInt<N / 2> &lower) : m_upper{0, branch_side_t::LEFT}, m_lower{lower},
                                                      m_overflown{false}, m_underflown{false},
                                                      c_branch_side{branch_side_t::ROOT}, p_parent{nullptr} {
    initialize_pointers();
}

template<uint16_t N>
LargeInt<N>::LargeInt(const LargeInt<N / 2> &upper,int) : m_upper{upper}, m_lower{0,branch_side_t::RIGHT},
                                                          m_overflown{false}, m_underflown{false},
                                                          c_branch_side{branch_side_t::ROOT}, p_parent{nullptr} {
    initialize_pointers();
}

template<uint16_t N>
LargeInt<N>::LargeInt(const LargeInt<N / 2> &upper,const LargeInt<N / 2> &lower) : m_upper{upper}, m_lower{lower},
                                                                                   m_overflown{false}, m_underflown{false},
                                                                                   c_branch_side{branch_side_t::ROOT}, p_parent{nullptr} {
    initialize_pointers();
}

template<uint16_t N>
LargeInt<N>::LargeInt(const std::string &str_repr) : m_upper{0, branch_side_t::LEFT}, m_lower{0, branch_side_t::RIGHT},
                                                     m_overflown{false}, m_underflown{false},
                                                     c_branch_side{branch_side_t::ROOT}, p_parent{nullptr} {
    initialize_pointers();

    for (const char c: str_repr) {
        this->multiply_by_ten(c - '0');
    }
}

// =====================================================================================================================

template<uint16_t N>
void LargeInt<N>::initialize_pointers(LargeInt<2 * N> *parent, LargeInt<8>** pp_last_leaf) {
    p_parent = parent;
    if (pp_last_leaf == nullptr) {
        LargeInt<8> *p_last_leaf = nullptr;
        m_upper.initialize_pointers(this, &p_last_leaf);
        m_lower.initialize_pointers(this, &p_last_leaf);
    } else {
        m_upper.initialize_pointers(this, pp_last_leaf);
        m_lower.initialize_pointers(this, pp_last_leaf);
    }
}

template<uint16_t N>
void LargeInt<N>::multiply_by_ten(uint8_t carry) {
    m_lower.multiply_by_ten(carry);
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


#endif //LARGE_INT_DETAILS_MEMBER_CORE_HPP
