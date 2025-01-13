#include <iostream>
#include "LargeInt.hpp"

int main() {

//    LargeInt<512> test{};

    LargeInt<16> a = LargeInt<16>{200};
    LargeInt<16> b = LargeInt<16>{10};

    std::cout << a << "\n";
    std::cout << b << "\n";

//    std::cout << "0: " << (a << 0) << "\n";
//    std::cout << "1: " << (a << 1) << "\n";
//    std::cout << "2: " << (a << 2) << "\n";
//    std::cout << "3: " << (a << 3) << "\n";
//    std::cout << "4: " << (a << 4) << "\n";
//    std::cout << "6: " << (a << 6) << "\n";
//    std::cout << "8: " << (a << 8) << "\n";
//    std::cout << "10: " << (a << 10) << "\n";
//    a *= b;

    std::cout << (a *= 2) << "\n";


    return 0;
}