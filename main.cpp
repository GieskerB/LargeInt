#include <iostream>

#include "include/large_int/large_int.hpp"

int main() {
    LargeInt<16> num{"10000"};
    std::cout << num << std::endl;
    return 0;
}