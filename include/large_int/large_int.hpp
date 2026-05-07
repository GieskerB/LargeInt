#ifndef LARGE_INT_HPP
#define LARGE_INT_HPP

#include <cstdint>

template<uint16_t N>
class LargeInt;

// TODO: documentation
// TODO: optimization
      // reduce #of LargeInt initializations
      // Move semantic
      // initialize_pointers() Overhead

#include "large_int_8.hpp"
#include "large_int_core.hpp"

#include "large_int/operators/output.hpp"

#endif //LARGE_INT_HPP