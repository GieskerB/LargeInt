#ifndef LARGEINT_LARGE_INT_HPP
#define LARGEINT_LARGE_INT_HPP

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

#include "operators/output.hpp"

#endif //LARGEINT_LARGE_INT_HPP