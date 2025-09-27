#include <iostream>
#include "large_int/LargeInt.hpp"

int main() {

    LargeInt<64> li{12};
    li <<= 11;

    std::cout << li <<"|" << 24576 << std::endl;

    return 0;
}
