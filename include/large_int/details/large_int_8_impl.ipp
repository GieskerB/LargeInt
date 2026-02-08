#ifndef LARGEINT_LARGE_INT_8_IMPL_IPP
#define LARGEINT_LARGE_INT_8_IMPL_IPP

#include "../large_int_8.hpp"
#include "../large_int_core.hpp"

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

inline thread_local LargeInt<8>* p_last_leaf = nullptr;
template<uint16_t N>
void LargeInt<N>::initialize_pointers(LargeInt<2 * N> *parent) {
    if (c_branch_side == branch_side_t::ROOT) p_last_leaf = nullptr;
    p_parent = parent;
    m_upper.initialize_pointers(this);
    m_lower.initialize_pointers(this);
}

template<uint16_t N>
uint16_t LargeInt<N>::get_msb_index(bool init_call) const {
    return init_call ? N - m_upper.get_msb_index(false) : m_upper.get_msb_index(false);
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

#endif //LARGEINT_LARGE_INT_8_IMPL_IPP