#ifndef LARGE_INT_OPERATORS_8_UNARY_HPP
#define LARGE_INT_OPERATORS_8_UNARY_HPP

inline LargeInt<8> LargeInt<8>::operator+() const {
    return *this;
}

inline LargeInt<8> LargeInt<8>::operator-() const {
    throw std::runtime_error("Can not invert LargeInt due to being unsigned");
}

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
