#ifndef LARGEINT_BRANCH_SIDE_HPP
#define LARGEINT_BRANCH_SIDE_HPP

#include <cstdint>

/**
 * @enum branch_side_t
 * @brief Identifier with three possible values.
 * Needed for tree like structure of LargeInt. Holds the information about relative position to parent.
 *
 */
enum class branch_side_t : int8_t {
    /// Left or upper part of its parent.
    LEFT = -1,
    /// Right or lower part of its parent.
    RIGHT = 1,
    /// Root or top part of whole LargeInt. A LargeInt classified as ROOT should not have a parent.
    ROOT = 0
};

#endif //LARGEINT_BRANCH_SIDE_HPP