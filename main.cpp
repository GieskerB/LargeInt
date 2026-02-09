#include <iostream>

#include "include/large_int/large_int.hpp"

int main() {
    LargeInt<32> number{123};

    std::cout << number << "\n";

}