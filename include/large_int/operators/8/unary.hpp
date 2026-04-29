#ifndef LARGE_INT_OPERATORS_8_UNARY_HPP
#define LARGE_INT_OPERATORS_8_UNARY_HPP

inline LargeInt<8> &LargeInt<8>::operator++() {
    *this += 1;
    return *this;
}

inline LargeInt<8> &LargeInt<8>::operator--() {
    *this -= 1;
    return *this;
}

inline LargeInt<8> LargeInt<8>::operator++(int) {
    LargeInt<8> res{*this};
    ++*this;
    return res;
}

inline LargeInt<8> LargeInt<8>::operator--(int) {
    LargeInt<8> res{*this};
    --*this;
    return res;
}

#endif //LARGE_INT_OPERATORS_8_UNARY_HPP
