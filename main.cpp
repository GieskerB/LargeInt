#include <iostream>

#include "include/large_int/large_int.hpp"

int main() {

    LargeInt<32> a {"10000"};
    LargeInt<32> b {"500"};

    LargeInt<32> c = a / b; //20

    std::cout << c << "\n";

    return 0;
}