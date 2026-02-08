#ifndef LARGEINT_BRANCH_SIDE_HPP
#define LARGEINT_BRANCH_SIDE_HPP

#include <cstdint>

enum class branch_side_t : int8_t {
    LEFT = -1, RIGHT = 1, ROOT = 0
};

#endif //LARGEINT_BRANCH_SIDE_HPP