#include <iostream>
#include "large_int/LargeInt.hpp"

int main() {
    LargeInt<32> c{123};

    std::cout << c<< '\n';
    std::cout << c++<< '\n';
    std::cout << c--<< '\n';
    std::cout << "---\n";
    std::cout << c<< '\n';
    std::cout << --c<< '\n';
    std::cout << ++c<< '\n';

    return 0;
}
