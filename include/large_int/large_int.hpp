#ifndef LARGEINT_LARGE_INT_HPP
#define LARGEINT_LARGE_INT_HPP

#include <cstdint>

template<uint16_t N>
class LargeInt;

static int counter = 0;

// TODO: working division operator
// TODO: propper tests for all operators
      // shift operator
      // sub operator
// TODO: documentation
// TODO: optimization
      // reduce #of LargeInt initilaizations
      // Move semantic
      // initialize_pointers() Overhead

#include "large_int_8.hpp"
#include "large_int_core.hpp"

#include "operators/output.hpp"

#endif //LARGEINT_LARGE_INT_HPP