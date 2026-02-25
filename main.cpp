#include <iostream>

#include "include/large_int/large_int.hpp"

int main() {
    LargeInt<64> a{"18446744073709551615"};
    auto b = a * a;
    std::cout << b << std::endl;
    return 0;
}