#ifndef LARGE_INT_8_HPP
#define LARGE_INT_8_HPP

/** @file large_int_8.hpp */

#include <compare>
#include <string>
#include <stdexcept>
#include <limits>

#include "details/branch_side.hpp"

/**
 * @brief Base class of recursive class design.
 * @tparam N number of bits. Set to 8.
 * The recursive design must stop at some point. Using 8 Bit as the smallest type ensures, that this can run on any hardware supporting 16 bit arithmetic. Therefore, the usage of small LargeInts with 8 or 16 bits is supported.
 */
template<>
class LargeInt<8> {

    // Friend declarations:
    template<uint16_t M> friend
    class LargeInt; // This is the "big brother".
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

    /** @constructDef */
    LargeInt();

    /** @constructInt*/
    LargeInt(uint8_t);

    /** @constructCopy */
    LargeInt(const LargeInt<8> &);

    /**
     * @constructStr
     * Useless for LargeInt<8> due to storage limit up to 255 which can be initialized with standard constructor.
     */
    explicit LargeInt(const std::string &);

    /** @overflown */
    bool was_overflow();
    /** @underflown */
    bool was_underflow();

    // =================================================================================================================

    /**
     * @name Arithmetic Operators
     * @brief Standard mathematical and bitwise operations.
     * @{
     */
    /** @add{new} */
    LargeInt<8> operator+(const LargeInt<8> &) const;

    /** @subtract{new} */
    LargeInt<8> operator-(const LargeInt<8> &) const;

    /** @multiply{new}] */
    LargeInt<16> operator*(const LargeInt<8> &) const;

    /** @divide{quotient, new} */
    LargeInt<8> operator/(const LargeInt<8> &) const;

    /** @divide{remainder, new} */
    LargeInt<8> operator%(const LargeInt<8> &) const;

    /** @bitwiseNot{new} */
    LargeInt<8> operator~() const;

    /** @bitwise{AND, ands, new} */
    LargeInt<8> operator&(const LargeInt<8> &) const;

    /** @bitwise{OR, ors, new} */
    LargeInt<8> operator|(const LargeInt<8> &) const;

    /** @bitwise{XOR, xors, new} */
    LargeInt<8> operator^(const LargeInt<8> &) const;

    /** @bitshift{Left, left, new} */
    LargeInt<8> operator<<(uint16_t) const;

    /** @bitshift{Right, right, new} */
    LargeInt<8> operator>>(uint16_t) const;
    /** @} */

    // =================================================================================================================

    /**
     * @name Assignment Operators
     * @brief Standard mathematical and bitwise operations.
     * @{
     */
     /** @assign */
    LargeInt<8> &operator=(const LargeInt<8> &);

    /** @add{this} */
    LargeInt<8> &operator+=(const LargeInt<8> &);

    /** @subtract{this} */
    LargeInt<8> &operator-=(const LargeInt<8> &);

    /** @multiply{this}] */
    LargeInt<8> &operator*=(const LargeInt<8> &);

    /** @divide{quotient, this} */
    LargeInt<8> &operator/=(const LargeInt<8> &);

    /** @divide{remainder, this} */
    LargeInt<8> &operator%=(const LargeInt<8> &);

    /** @bitwise{AND, ands, this} */
    LargeInt<8> &operator&=(const LargeInt<8> &);

    /** @bitwise{OR, ors, this} */
    LargeInt<8> &operator|=(const LargeInt<8> &);

    /** @bitwise{XOR, xors, this} */
    LargeInt<8> &operator^=(const LargeInt<8> &);

    /** @bitshift{Left, left, this} */
    LargeInt<8> &operator<<=(uint16_t);

    /** @bitshift{Right, right, this} */
    LargeInt<8> &operator>>=(uint16_t);
    /** @} */

    // =================================================================================================================

    /**
     * @name Comparison Operators
     * @brief Standard mathematical and bitwise operations.
     * @{
     */
    /** @compareEqual */
    bool operator==(const LargeInt<8> &) const;

    /** @compareSpaceship */
    std::strong_ordering operator<=>(const LargeInt<8> &) const;
    /** @} */

    // =================================================================================================================

    /**
     * @name In- / Decrement Operators
     * @brief Standard mathematical and bitwise operations.
     * @{
     */
    /** @prefix{increment, Increases} */
    LargeInt<8> &operator++();

    /** @prefix{decrement, Decreases} */
    LargeInt<8> &operator--();

    /** @postfix{increment, Increases} */
    LargeInt<8> operator++(int);

    /** @postfix{decrement, Decreases} */
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

#include "details/member_8.hpp"
#include "operators/all_8.hpp"

#endif //LARGE_INT_8_HPP
