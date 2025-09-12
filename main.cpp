#include <iostream>
#include "LargeInt.hpp"

int main() {
    LargeInt<32> c{123};

    std::cout << c.get_msb_index() << "~" << c << "\n";
    c += 1;
    std::cout << c.get_msb_index() << "~" << c << "\n";
    for (int i = 0; i < 10; ++i) {
        c <<= 1;
        std::cout << c.get_msb_index() << "~" << c << "\n";
    }

    return 0;
}
