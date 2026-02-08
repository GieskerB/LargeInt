//
// Created by bjarn on 19.01.2025.
//

#ifndef LARGEINT_GENERAL_IN_DE_CREMENT_HPP
#define LARGEINT_GENERAL_IN_DE_CREMENT_HPP

template<uint16_t N>
LargeInt<N> LargeInt<N>::operator++() {
    LargeInt<N> copy{*this};
    *this += 1;
    return copy;
}

template<uint16_t N>
LargeInt<N> LargeInt<N>::operator--() {
    LargeInt<N> copy{*this};
    *this -= 1;
    return copy;
}

template<uint16_t N>
LargeInt<N> &LargeInt<N>::operator++(int) {
    *this += 1;
    return *this;

}

template<uint16_t N>
LargeInt<N> &LargeInt<N>::operator--(int) {
    *this -= 1;
    return *this;
}

#endif //LARGEINT_GENERAL_IN_DE_CREMENT_HPP
