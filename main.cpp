#include <iostream>

#include "include/large_int/large_int.hpp"

int main() {
    std::cout << "static counter - 1: " << counter <<"\n";
    LargeInt<64> llong1{"123456789"};
    std::cout << "static counter - 2: " << counter << "\n";
    LargeInt<64> llong2{"987654321"};
    std::cout << "static counter - 3: " << counter << "\n";
    LargeInt<128> llong3 = llong1 * llong2; // 1B13114FBFF5385
    std::cout << "static counter - 4: " << counter << "\n";

    std::cout << llong3 << "\n";

    // 4876
    // 3432
    // 397
    // 259

}