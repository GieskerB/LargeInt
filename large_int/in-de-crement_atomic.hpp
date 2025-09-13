#ifndef LARGEINT_ATOMIC_IN_DE_CREMENT_HPP
#define LARGEINT_ATOMIC_IN_DE_CREMENT_HPP

inline LargeInt<8> &LargeInt<8>::operator++() {
    *this+=1;
    return *this;
}

inline LargeInt<8> &LargeInt<8>::operator--() {
    *this-=1;
    return *this;
}

inline LargeInt<8> LargeInt<8>::operator++(int)  {
    LargeInt<8> res{*this};
    ++*this;
    return res;
}

inline LargeInt<8> LargeInt<8>::operator--(int) {
    LargeInt<8> res{*this};
    --*this;
    return res;
}

#endif //LARGEINT_ATOMIC_IN_DE_CREMENT_HPP
