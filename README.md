# LargeInt

LargeInt is a C++ header library designed to create unsigned integers of almost any size. With the templated class
design, LargeInt supports the following bit sizes $N$ as long they are a power of two:

$$
8 \leq N \leq 32768 \land N = 2^k \forall k\in \mathbb N
$$

To deal with possible so large numbers algorithmic wise, the class has a recursive structure, where each LargeInt holds
an upper and lower part, each with half the size. This recursion stops at $N$ = 8. Therefore, this library is based on
8-bit numbers and arithmetic, which should be supported on any modern hardware - even microcontrollers. 

The main reason for starting this project, was the Karatsuba algorithm which I learned about in university. This
algorithm supports multiplication for any size number by recursively splitting the workload more efficient then the
standard school method would do.

Implementation of the division operator was the most tedious part of this project. Finding and implementing a division
operation that is compatible with this design was more challenging than expected. In the end, the Burnikel Ziegler
division algorithm saved the day.

## Installation

Download the headers and include the inlcude/large_int/ folder in you project with `-I` argument.

## Usage

Once `large_int.hpp` is included, you can use the `LargeInt<N>` class. It supports all standard arithmetic, comparison
and unary operators excluding the unary `+` and `-` operator. Read the documentation for more info about each operator
if needed.

**Note:** All operators but the multiplication return a LargeInt with the same size $N$. Only the multiplication will
return a LargeInt of size $2N$. Otherwise, information may be lost for big numbers. Ony LargeInt with the same bit width
can be used together in one operator call. However, up- and downcasting is supported, so this should not create any
issues.

### Example code

```c++
#include "large_int.hpp"
#include <iostream>

int main() {
    LargeInt<128> num1("1234567890123456789");
    LargeInt<128> num2(1);
    
    auto res = num1 + num2;
    std::cout << res;
}

```

## License

[MIT](https://choosealicense.com/licenses/mit/)