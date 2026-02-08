#ifndef LARGEINT_SPECIFIC_IN_DE_CREMENT_HPP
#define LARGEINT_SPECIFIC_IN_DE_CREMENT_HPP

LargeInt<8>  LargeInt<8>::operator++() {
    LargeInt<8> copy{*this};
    *this += 1;
    return copy;
}
LargeInt<8> LargeInt<8>::operator--(){
    LargeInt<8> copy{*this};
    *this -= 1;
    return copy;
}
LargeInt<8> & LargeInt<8>::operator++(int){
    *this += 1;
    return *this;

}
LargeInt<8> & LargeInt<8>::operator--(int){
    *this -= 1;
    return *this;
}


#endif //LARGEINT_SPECIFIC_IN_DE_CREMENT_HPP
