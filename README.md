# LargeInt
LargeInt is a C++ library for handling arbitrarily large integers with custom bit sizes.
It supports standard arithmetic operations like addition, subtraction, multiplication,
and bit shifting, while managing overflow and underflow. The library allows efficient handling
of large numbers and can be used in standard expressions with any bit size.

## Idea:
In university, I have learned about the Karazuba-Multiplication. I wanted to implement this in
code and thought to myself: If I implement this multiplication for my custom data structure,
why not finish it and add the other important arithmetic operations.

## Design:
LargeInt is a recursively design class which stores a left and right half of the number as a
separate instance of the LargeInt class with only half the size each. This described recursions comes to
a hold when the number of bits reaches 8. Therefore, only a number of bits '$N$' in the form of
$N = 2^k\colon k \in \mathbb N$ is allowed.

## Currently supported operations:
- addition
- subtraction
- multiplication
- L-bitshift