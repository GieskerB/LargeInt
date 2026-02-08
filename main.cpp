#include <iostream>
#include "large_int/LargeInt.hpp"

int main() {

//    LargeInt<512> test{};

    LargeInt<64> a {210};
    LargeInt<64> b {234};

    std::cout << a << "\n";
    std::cout << b << "\n";

    a /= b;

    std::cout << a << "\n";


    return 0;
}