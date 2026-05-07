#include <iostream>

#include "include/large_int/large_int.hpp"

int main() {

    LargeInt<512> a {"340282366920938463463374607431768211455"};
    LargeInt<512> b {"5"};

    auto c = a / b; //68056473384187692692674921486353642291
    std::cout << "68056473384187692692674921486353642291\n";

    std::cout << c << "\n";

    return 0;
}
