#ifndef TESTING_LARGEINT_GENERAL_HPP
#define TESTING_LARGEINT_GENERAL_HPP

#include <cstdint>
#include <stdexcept>
#include <limits>
#include <iostream>

enum class branch_side_t : int8_t {
    LEFT = -1, RIGHT = 1, NONE = 0
};

template<uint16_t N>
class LargeInt {
public:
    LargeInt<N / 2> m_upper, m_lower;
    bool m_overflown, m_underflown;
    branch_side_t c_branch_side;

    LargeInt<2 * N> *p_parent;


    LargeInt(uint8_t, LargeInt<2 * N> *, branch_side_t);

    LargeInt<8> *assent(branch_side_t, branch_side_t);

    LargeInt<8> *decent(branch_side_t, bool);

    void initialize_neighbors();
    LargeInt(LargeInt<N/2>&);

public:
    LargeInt();
    static LargeInt<N> create_instance(uint8_t = 0);

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

    bool operator==(const LargeInt<N> &) const;

    std::strong_ordering operator<=>(const LargeInt<N> &) const;
};

/*
 * +------------+
 * |Constructors|
 * +------------+
 */


template<uint16_t N>
LargeInt<N>::LargeInt() : LargeInt<N>{0, nullptr,branch_side_t::NONE}  {
}

template<uint16_t N>
LargeInt<N>::LargeInt(uint8_t init_value, LargeInt<2 * N> *parent_ptr, enum branch_side_t b_side)
        :  m_upper{0, this, branch_side_t::LEFT}, m_lower{init_value, this, branch_side_t::RIGHT}, m_overflown{false},
           m_underflown{false}, c_branch_side{b_side}, p_parent{parent_ptr} {
    if ((N & (N - 1)) != 0) {
        //Not a perfect power of 2!
        throw std::runtime_error("LargeInt in only supports a perfect power of 2 number of Bits.");
    }
}

template<uint16_t N>
LargeInt<N>::LargeInt(LargeInt<N / 2> & lower):  m_upper{0, this, branch_side_t::LEFT}, m_lower{lower}, m_overflown{false},
                                           m_underflown{false}, c_branch_side{branch_side_t::NONE}, p_parent{nullptr} {
    m_lower.c_branch_side = branch_side_t::RIGHT;
    m_lower.p_parent = this;
}

/*
 * +----------------------+
 * |Methods implementation|
 * +----------------------+
 */

template<uint16_t N>
LargeInt<8> *LargeInt<N>::assent(branch_side_t coming, branch_side_t heading) {
    if (coming == branch_side_t::LEFT and heading == branch_side_t::RIGHT) {
        return m_lower.decent(branch_side_t::NONE, true);
    } else if (coming == branch_side_t::RIGHT and heading == branch_side_t::LEFT) {
        return m_upper.decent(branch_side_t::NONE, true);
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

template <uint16_t N>
void LargeInt<N>::initialize_neighbors() {
    m_upper.initialize_neighbors();
    m_lower.initialize_neighbors();
}

template<uint16_t N>
LargeInt<8> *LargeInt<N>::get_brother(branch_side_t coming, branch_side_t heading) {
    if (coming == branch_side_t::NONE or heading == branch_side_t::NONE) {
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
 * +-----------------------------+
 * |Static methods implementation|
 * +-----------------------------+
 */

template<uint16_t N>
LargeInt<N> LargeInt<N>::create_instance(uint8_t init_value) {
    LargeInt<N> instance{init_value, nullptr, branch_side_t::NONE };
    instance.initialize_neighbors();
    return instance;
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
        m_upper += LargeInt<N/2>::create_instance(1);
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
        std::cout << "underflow " << N << "\n";
        m_upper -= LargeInt<N / 2>::create_instance(1);
    }
    m_underflown = m_upper.was_underflow();

    return *this;
}

template<uint16_t N>
LargeInt<2 * N> LargeInt<N>::operator*(const LargeInt<N> & other) const {
    // TODO Karatsuba

    const LargeInt< N> upper_times_upper = m_upper * other.m_upper;
    const LargeInt< N> lower_times_lower = m_lower * other.m_lower;
    LargeInt<N> special_product = (m_upper + m_lower) * (other.m_upper + other.m_lower);

    // TODO cast in next bigger Large Int

    LargeInt<2*N> result{};
    result.m_upper = upper_times_upper;
    result.m_lower = lower_times_lower;

    LargeInt<2*N> tmp{special_product};
    tmp.initialize_neighbors();

    tmp <<= N/2;
    result += tmp;
    return result;
}

template<uint16_t N>
LargeInt<N> &LargeInt<N>::operator*=(const LargeInt<N> &other) {
    LargeInt<2*N>  res = *this * other;
    *this = res.m_lower;
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
