#include <iostream>
#include "LargeInt.hpp"

int main() {


    LargeInt<16> a = LargeInt<16>::create_instance(60);
    LargeInt<16> b = LargeInt<16>::create_instance(30);

    std::cout << a << "\n";
    std::cout << b << "\n";

    a += b;

    a *= b;

    std::cout << a<< "\n";
    a <<= 3;

    std::cout << a << "\n";

    return 0;
}