#ifndef LARGEINT_LARGE_INT_8_HPP
#define LARGEINT_LARGE_INT_8_HPP

#include <compare>
#include <string>
#include <stdexcept>
#include <limits>

#include "details/branch_side.hpp"

/**
 * @brief Base class of recursive class design.
 * @tparam N number of bits. Set to 8.
 * The recursive design must stop at some point. Using 8 Bit as the smallest type ensures, that this can run on any
 * hardware supporting 16 bit arithmetic. Therefore, the usage of small LargeInts with 8 or 16 bits is supported.
 */
template<>
class LargeInt<8> {

    // Friend declarations:
    template<uint16_t M> friend
    class LargeInt; // This is the "big brother". Large recursive structure.
    friend void output_hex(std::ostream &, const LargeInt<8> &, const uint16_t);
    friend void output_bin(std::ostream &, const LargeInt<8> &, const uint16_t);
    friend uint64_t to_decimal(const LargeInt<8> &);

    /// Stores one single byte of the possibly huge LargeInt instance.
    uint8_t m_value;

    /// Temporal values used to make addition and subtraction easier.
    bool m_overflown, m_underflown;

    /// Remembers if instance is the upper or lower part of parent instance.
    const branch_side_t c_branch_side;

    /// For easier traversal in huge LargeInts, an instance stores a pointer to its parent.
    LargeInt<16> *p_parent;
    /// For easier traversal only the LargeInt<8> knows its left and right sibling.
    LargeInt<8> *p_left, *p_right;

    /// Only used internal. Called by bigger LargeInts to parse the branching direction.
    LargeInt(uint8_t, branch_side_t);

    /**
     * @brief Called at the very end of the constructor. Needed to setup left, right and parent pointers.
     * @param parent point to the parent (very clear).
     * @param pp_last_leaf pointer to pointer to last leaf. Extra pointer needed for correct behaviour. After reading set pointer pointer to 'this'.
     */
    void initialize_pointers(LargeInt<16> * = nullptr, LargeInt<8> ** = nullptr);

    /// Efficient multiply by 10 + carry operator for reading strings. Faster then Karatsuba -> O(n)
    void multiply_by_ten(uint8_t carry = 0);

    /// Get respective bits from possibly distant neighbor. Used for bit shifting to prevent data loss with minimal overhead.
    [[nodiscard]] uint8_t get_upper_bits(uint16_t, branch_side_t) const;
    [[nodiscard]] uint8_t get_lower_bits(uint16_t, branch_side_t) const;

public:

    /**
     * @brief Default constructor. Initializes LargeInt with 0.
     */
    LargeInt();

    /**
     * @brief Standard constructor. Initializes LargeInt with number between 0 and 255.
     */
    LargeInt(uint8_t);

    /**
     * @brief Copy constructor.
     * @param copy Instance that is copied.
     */
    LargeInt(const LargeInt<8> &);

    /**
     * @breif String constructor. Initializes Large in based on numeric value in string.
     * @param str_repr String representation of the number in base 10.
     * Useless for LargeInt<8> due to storage limit up to 255 which can be initialized with standard constructor.
     */
    explicit LargeInt(const std::string &);

    /**
     * @brief Check if last addition lead to an overflow.
     * Automatically resets information after calling this function.
     * @return true if addition resulted in an overflow.
     */
    bool was_overflow();

    /**
     * @brief Check if last subtraction lead to an underflow.
     * Automatically resets information after calling this function.
     * @return true if subtraction resulted in an underflow.
     */
    bool was_underflow();

    // =================================================================================================================

    /**
     * @name Arithmetic Operators
     * @brief Standard mathematical and bitwise operations.
     * @{
     */
    /**
     * @brief Turns this number positive.
     * @note It is already positive - by design. Function has not effect.
     * @return this object.
     */
    LargeInt<8> operator+() const;
    /**
     * @brief Inverts the LargeInt.
     * @note Inverting a unsigned value is not possible. This will therefore, thrown an exception.
     * @exception std::runtime_error
     */
    LargeInt<8> operator-() const;
    /**
     * @brief Add this with another LargeInt.
     * @param other Right addend of calculation.
     * @return new LargeInt object that contains the sum.
     */
    LargeInt<8> operator+(const LargeInt<8> &) const;
    /**
     * @brief Subtracts another LargeInt from this.
     * @param other Subtrahend of calculation.
     * @return new LargeInt object that contains the difference.
     */
    LargeInt<8> operator-(const LargeInt<8> &) const;
    /**
     * @brief Multiplies this with another LargeInt.
     * @note This operation returns a LargeInt<16> to prevent overflow.
     * For better efficiency this operator used the Karatsuba multiplication with a time complexity in
     * O(n^(1.585)). Compared to the standard school book complexity of O(n^2).
     * @param other Right factor of calculation.
     * @return new LargeInt object that contains the product.
     */
    LargeInt<16> operator*(const LargeInt<8> &) const;
    /**
     * @brief Divides this with another LargeInt for the integer quotient.
     * For better efficiency this operator used the Burnikel-Ziegler division. Need to support division even for very
     * LargeInts
     * @exception std::exception Thrown if other is zero.
     * @param other Divisor of calculation.
     * @return new LargeInt object that contains the integer quotient.
     */
    LargeInt<8> operator/(const LargeInt<8> &) const;
    /**
     * @brief Divides this with another LargeInt for the integer remainder.
     * For better efficiency this operator used the Burnikel-Ziegler division. Need to support division even for very
     * LargeInts
     * @exception std::exception Thrown if other is zero.
     * @param other Divisor of calculation.
     * @return new LargeInt object that contains the integer remainder.
     */
    LargeInt<8> operator%(const LargeInt<8> &) const;
    /**
     * @brief Bitwise NOT. Inverts all bits int he number.
     * @return new LargeInt object that contains the result.
     */
    LargeInt<8> operator~() const;
    /**
     * @brief Bitwise AND. Logically ands every bits with the respective bit from the other LargeInt.
     * @param other Right hand-side of the operation.
     * @return new LargeInt object that contains the result.
     */
    LargeInt<8> operator&(const LargeInt<8> &) const;
    /**
     * @brief Bitwise OR. Logically ors every bits with the respective bit from the other LargeInt.
     * @param other Right hand-side of the operation.
     * @return new LargeInt object that contains the result.
     */
    LargeInt<8> operator|(const LargeInt<8> &) const;
    /**
     * @brief Bitwise XOR. Logically xors every bits with the respective bit from the other LargeInt.
     * @param other Right hand-side of the operation.
     * @return new LargeInt object that contains the result.
     */
    LargeInt<8> operator^(const LargeInt<8> &) const;
    /**
     * @brief Left bitshift. Shift the bits in the number left by the number provided as an argument.
     * @param shift Number of bits, the entire number is moved to the left.
     * @return new LargeInt object that contains the result.
     */
    LargeInt<8> operator<<(uint16_t) const;
    /**
     * @brief Right bitshift. Shift the bits in the number right by the number provided as an argument.
     * @param shift Number of bits, the entire number is moved to the right.
     * @return new LargeInt object that contains the result.
     */
    LargeInt<8> operator>>(uint16_t) const;
    /** @} */

    // =================================================================================================================

    /**
     * @name Assignment Operators
     * @brief Standard mathematical and bitwise operations.
     * @{
     */
    /**
     * @brief Assigns this LargeInt to other. Implicitly copying the object.
     * @param other LargeInt which values are assigned to this.
     * @return this LargeInt object containing the copy
     */
    LargeInt<8> &operator=(const LargeInt<8> &);
    /**
     * @brief Add this with another LargeInt.
     * @param other Right addend of calculation.
     * @return this LargeInt object containing the sum.
     */
    LargeInt<8> &operator+=(const LargeInt<8> &);
    /**
     * @brief Subtracts another LargeInt from this.
     * @param other Subtrahend of calculation.
     * @return this LargeInt object containing the difference.
     */
    LargeInt<8> &operator-=(const LargeInt<8> &);
    /**
     * @brief Multiplies this with another LargeInt.
     * @note This operation returns a LargeInt<16> to prevent overflow.
     * For better efficiency this operator used the Karatsuba multiplication with a time complexity in
     * O(n^(1.585)). Compared to the standard school book complexity of O(n^2).
     * @param other Right factor of calculation.
     * @return this LargeInt object containing the product.
     */
    LargeInt<8> &operator*=(const LargeInt<8> &);
    /**
     * @brief Divides this with another LargeInt for the integer quotient.
     * For better efficiency this operator used the Burnikel-Ziegler division. Need to support division even for very
     * LargeInts
     * @exception std::exception Thrown if other is zero.
     * @param other Divisor of calculation.
     * @return this LargeInt object containing the integer quotient.
     */
    LargeInt<8> &operator/=(const LargeInt<8> &);
    /**
     * @brief Divides this with another LargeInt for the integer remainder.
     * For better efficiency this operator used the Burnikel-Ziegler division. Need to support division even for very
     * LargeInts
     * @exception std::exception Thrown if other is zero.
     * @param other Divisor of calculation.
     * @return this LargeInt object containing the integer remainder.
     */
    LargeInt<8> &operator%=(const LargeInt<8> &);
    /**
     * @brief Bitwise AND. Logically ands every bits with the respective bit from the other LargeInt.
     * @param other Right hand-side of the operation.
     * @return this LargeInt object containing the result.
     */
    LargeInt<8> &operator&=(const LargeInt<8> &);
    /**
     * @brief Bitwise OR. Logically ors every bits with the respective bit from the other LargeInt.
     * @param other Right hand-side of the operation.
     * @return this LargeInt object containing the result.
     */
    LargeInt<8> &operator|=(const LargeInt<8> &);
    /**
     * @brief Bitwise XOR. Logically xors every bits with the respective bit from the other LargeInt.
     * @param other Right hand-side of the operation.
     * @return this LargeInt object containing the result.
     */
    LargeInt<8> &operator^=(const LargeInt<8> &);
    /**
     * @brief Left bitshift. Shift the bits in the number left by the number provided as an argument.
     * @param shift Number of bits, the entire number is moved to the left.
     * @return this LargeInt object containing the result.
     */
    LargeInt<8> &operator<<=(uint16_t);
    /**
     * @brief Right bitshift. Shift the bits in the number right by the number provided as an argument.
     * @param shift Number of bits, the entire number is moved to the right.
     * @return this LargeInt object containing the result.
     */
    LargeInt<8> &operator>>=(uint16_t);
    /** @} */

    // =================================================================================================================

    /**
     * @name Comparison Operators
     * @brief Standard mathematical and bitwise operations.
     * @{
     */
    /**
     * @brief Equal comparison operator. Used to compare LargeInt for equality.
     * @param other LargeInt to compare this to.
     * Implicitly generate operator!= automatically by C++
     * @return true if both LargeInts have the same numeric value.
     */
    bool operator==(const LargeInt<8> &) const;
    /**
     * @brief Spaceship operator. Implicitly generates all 4 unequal comparison operators automatically.
     * @param other LargeInt to compare this to.
     * Strong ordering provides a strict total ordering where equal values are logically indistinguishable and
     * substitutable. The normal operator>= etc. exist at compile time and can therefore be used by the programmer.
     * @return Strong ordering object. The "standard" operators return a boolean as expected.
     */
    std::strong_ordering operator<=>(const LargeInt<8> &) const;
    /** @} */

    // =================================================================================================================

    /**
     * @name In- / Decrement Operators
     * @brief Standard mathematical and bitwise operations.
     * @{
     */
    /**
     * @brief Prefix increment operator.
     * Increases value by one BEFORE reading the value
     * @return new LargeInt object that contains the new value.
     */
    LargeInt<8> &operator++();
    /**
     * @brief Prefix decrement operator.
     * Decreases value by one BEFORE reading the value
     * @return new LargeInt object that contains the new value.
     */
    LargeInt<8> &operator--();
    /**
     * @brief Postfix increment operator.
     * Increases value by one AFTER reading the value
     * @return new LargeInt object that contains the value before increment.
     */
    LargeInt<8> operator++(int);
    /**
     * @brief Postfix increment operator.
     * Decreases value by one AFTER reading the value
     * @return new LargeInt object that contains the value before decrement.
     */
    LargeInt<8> operator--(int);
    /** @} */

    /**
     * @brief type cast to uint64.
     * @return uint64 representation of this number.
     */
    explicit operator uint64_t() const {
        return m_value;
    }
};

#include "details/large_int_8_impl.hpp"
#include "details/large_int_8_operators.hpp"

#endif //LARGEINT_LARGE_INT_8_HPP