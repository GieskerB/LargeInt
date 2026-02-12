#ifndef LARGEINT_UNARY_HPP
#define LARGEINT_UNARY_HPP

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

#endif //LARGEINT_UNARY_HPP
