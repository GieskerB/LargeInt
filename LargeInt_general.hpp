#ifndef TESTING_LARGEINT_GENERAL_HPP
#define TESTING_LARGEINT_GENERAL_HPP

#include <cstdint>
#include <stdexcept>
#include <limits>
#include <iostream>


// =====================================================================================================================


enum class branch_side_t : int8_t {
    LEFT = -1, RIGHT = 1, ROOT = 0
};


// =====================================================================================================================


template<uint16_t N>
class LargeInt;

template<>
class LargeInt<8>;


// =====================================================================================================================


template<uint16_t N>
class LargeInt {

    template<uint16_t M>
    friend class LargeInt;

    friend std::ostream &operator<<(std::ostream &os, const LargeInt<8>& large_int);
    friend std::ostream &operator<<(std::ostream &os, const LargeInt<16>& large_int);
    friend std::ostream &operator<<(std::ostream &os, const LargeInt<32>& large_int);
    friend std::ostream &operator<<(std::ostream &os, const LargeInt<64>& large_int);

    LargeInt<N / 2> m_upper, m_lower;
    bool m_overflown, m_underflown;
    const branch_side_t c_branch_side;

    LargeInt<2 * N> *p_parent;

    LargeInt(uint8_t, branch_side_t);
    LargeInt(const LargeInt<N / 2> &);
    LargeInt<8> *assent(branch_side_t, branch_side_t);
    LargeInt<8> *decent(branch_side_t, bool);
    void initialize_pointers(LargeInt<2 * N> * = nullptr);

public:
    LargeInt();
    LargeInt(uint8_t);
    LargeInt(const LargeInt &);


    LargeInt<8> *get_brother(branch_side_t, branch_side_t);
    bool was_overflow();
    bool was_underflow();

    LargeInt<N> operator+(const LargeInt<N> &) const;
    LargeInt<N> &operator+=(const LargeInt<N> &);
    LargeInt<N> operator-(const LargeInt<N> &) const;
    LargeInt<N> &operator-=(const LargeInt<N> &);
    LargeInt<2 * N> operator*(const LargeInt<N> &) const;
    LargeInt<N> &operator*=(const LargeInt<N> &);
    LargeInt<N> operator<<(uint16_t) const;
    LargeInt<N> &operator<<=(uint16_t);

    LargeInt<N> &operator=(const LargeInt<N> &);
    bool operator==(const LargeInt<N> &) const;
    std::strong_ordering operator<=>(const LargeInt<N> &) const;
};

/*
 * +------------+
 * |Constructors|
 * +------------+
 */


template<uint16_t N>
LargeInt<N>::LargeInt() : LargeInt<N>{0} {
}


template<uint16_t N>
LargeInt<N>::LargeInt(uint8_t init_value): LargeInt<N>{init_value, branch_side_t::ROOT} {};

template<uint16_t N>
LargeInt<N>::LargeInt(uint8_t init_value, enum branch_side_t b_side)
        :  m_upper{0, branch_side_t::LEFT}, m_lower{init_value, branch_side_t::RIGHT}, m_overflown{false},
           m_underflown{false}, c_branch_side{b_side}, p_parent{nullptr} {
    if ((N & (N - 1)) != 0) {
        //Not a perfect power of 2!
        throw std::runtime_error("LargeInt in only supports a perfect power of 2 number of Bits.");
    }

    if (c_branch_side == branch_side_t::ROOT) {
        initialize_pointers();
    }

}

template<uint16_t N>
LargeInt<N>::LargeInt(const LargeInt<N> &copy): m_upper{copy.m_upper}, m_lower{copy.m_lower}, m_overflown{false},
                                                m_underflown{false}, c_branch_side{copy.c_branch_side},
                                                p_parent{nullptr} {
    if (c_branch_side == branch_side_t::ROOT) {
        initialize_pointers();
    }
}

template<uint16_t N>
LargeInt<N>::LargeInt(const LargeInt<N / 2> &lower):  m_upper{0, branch_side_t::LEFT}, m_lower{lower},
                                                m_overflown{false},
                                                m_underflown{false}, c_branch_side{branch_side_t::ROOT},
                                                p_parent{nullptr} {
    initialize_pointers(nullptr);
}

/*
 * +----------------------+
 * |Methods implementation|
 * +----------------------+
 */

template<uint16_t N>
LargeInt<8> *LargeInt<N>::assent(branch_side_t coming, branch_side_t heading) {
    if (coming == branch_side_t::LEFT and heading == branch_side_t::RIGHT) {
        return m_lower.decent(branch_side_t::ROOT, true);
    } else if (coming == branch_side_t::RIGHT and heading == branch_side_t::LEFT) {
        return m_upper.decent(branch_side_t::ROOT, true);
    }
    if (p_parent == nullptr) {
        return nullptr;
    }
    return p_parent->assent(c_branch_side, heading);
}

template<uint16_t N>
LargeInt<8> *LargeInt<N>::decent(branch_side_t direction, bool is_first_decent) {

    if (is_first_decent) {
        if (direction == branch_side_t::LEFT) {
            return m_upper.decent(branch_side_t::RIGHT, false);
        } else {
            return m_lower.decent(branch_side_t::LEFT, false);
        }
    }
    if (direction == branch_side_t::LEFT) {
        return m_upper.decent(direction, false);
    } else {
        return m_lower.decent(direction, false);
    }

}

template<uint16_t N>
void LargeInt<N>::initialize_pointers(LargeInt<2 * N> *parent) {
    p_parent = parent;
    m_upper.initialize_pointers(this);
    m_lower.initialize_pointers(this);
}

template<uint16_t N>
LargeInt<8> *LargeInt<N>::get_brother(branch_side_t coming, branch_side_t heading) {
    if (coming == branch_side_t::ROOT or heading == branch_side_t::ROOT) {
        throw std::runtime_error("Can not find brother of node if either coming or heading from NONE!");
    }
    return assent(coming, heading);
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

/*
 * +-----------------------+
 * |Operator implementation|
 * +-----------------------+
 */

template<uint16_t N>
LargeInt<N> LargeInt<N>::operator+(const LargeInt<N> &other) const {
    LargeInt<N> res{*this};
    res += other;
    return res;
}

template<uint16_t N>
LargeInt<N> &LargeInt<N>::operator+=(const LargeInt<N> &other) {
    m_lower += other.m_lower;
    m_upper += other.m_upper;

    if (m_lower.was_overflow()) {
        m_upper += 1;
    }
    m_overflown = m_upper.was_overflow();

    return *this;
}

template<uint16_t N>
LargeInt<N> LargeInt<N>::operator-(const LargeInt<N> &other) const {
    LargeInt<N> res{*this};
    res -= other;
    return res;
}

template<uint16_t N>
LargeInt<N> &LargeInt<N>::operator-=(const LargeInt<N> &other) {
    m_lower -= other.m_lower;
    m_upper -= other.m_upper;

    if (m_lower.was_underflow()) {
        m_upper -= 1;
    }
    m_underflown = m_upper.was_underflow();

    return *this;
}

template<uint16_t N>
LargeInt<2 * N> LargeInt<N>::operator*(const LargeInt<N> &other) const {
    const LargeInt<N> upper_times_upper = m_upper * other.m_upper;
    const LargeInt<N> lower_times_lower = m_lower * other.m_lower;
    LargeInt<2 * N> special_product{(m_upper + m_lower) * (other.m_upper + other.m_lower)};

    LargeInt<2 * N> result{};
    result.m_upper = upper_times_upper;
    result.m_lower = lower_times_lower;
    result.initialize_pointers();

    special_product -= lower_times_lower;
    special_product -= upper_times_upper;
    special_product <<= N / 2;
    result += special_product;
    return result;
}

template<uint16_t N>
LargeInt<N> &LargeInt<N>::operator*=(const LargeInt<N> &other) {
    *this = (*this * other).m_lower;
    return *this;
}


template<uint16_t N>
LargeInt<N> LargeInt<N>::operator<<(uint16_t shift) const {
    LargeInt<N> res{*this};
    res <<= shift;
    return res;
}

template<uint16_t N>
LargeInt<N> &LargeInt<N>::operator<<=(uint16_t shift) {
    m_upper <<= shift;
    return *this;
}


template<uint16_t N>
LargeInt<N> &LargeInt<N>::operator=(const LargeInt<N> &copy) {
    m_upper = copy.m_upper;
    m_lower = copy.m_lower;
    m_overflown = copy.m_overflown;
    m_underflown = copy.m_underflown;
    const_cast<branch_side_t &>(c_branch_side) = copy.c_branch_side;
    initialize_pointers(nullptr);
    return *this;
}

template<uint16_t N>
bool LargeInt<N>::operator==(const LargeInt<N> &other) const {
    return std::is_eq(*this <=> other);
}


template<uint16_t N>
std::strong_ordering LargeInt<N>::operator<=>(const LargeInt<N> &other) const {
    auto ordering = m_upper <=> other.m_upper;
    if (ordering == std::strong_ordering::equal or ordering == std::strong_ordering::equivalent) {
        return m_lower <=> other.m_lower;
    }
    return ordering;
}

#endif //TESTING_LARGEINT_GENERAL_HPP
