#ifndef LARGE_INT_OPERATORS_CORE_UNARY_HPP
#define LARGE_INT_OPERATORS_CORE_UNARY_HPP

/** @file unary.hpp */

template<uint16_t N>
LargeInt<N> &LargeInt<N>::operator++() {
    *this+=1;
    return *this;
}

template<uint16_t N>
LargeInt<N> &LargeInt<N>::operator--() {
    *this-=1;
    return *this;
}

template<uint16_t N>
LargeInt<N> LargeInt<N>::operator++(int) {
    LargeInt<N> res{*this};
    ++*this;
    return res;

}

template<uint16_t N>
LargeInt<N> LargeInt<N>::operator--(int) {
    LargeInt<N> res{*this};
    --*this;
    return res;
}

#endif //LARGE_INT_OPERATORS_CORE_UNARY_HPP
