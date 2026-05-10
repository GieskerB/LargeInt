#ifndef LARGE_INT_CORE_HPP
#define LARGE_INT_CORE_HPP

/** @file large_int_core.hpp */

namespace bz_algo {
    template<uint16_t N>
    std::pair<LargeInt<N/2>, LargeInt<N/2>> div_2n_1n(const LargeInt<N>& A, const LargeInt<N/2>& B);

    template<uint16_t N>
    std::pair<LargeInt<N/2>, LargeInt<N>> div_3n_2n(const LargeInt<N>& A_12, const LargeInt<N/2>& A_3, const LargeInt<N>& B);

    template<uint16_t N>
    std::pair<LargeInt<N>, LargeInt<N>> div_mod_bz(const LargeInt<N>& numerator, const LargeInt<N>& denominator);
}

/**
 * @brief Larger class of recursive class design.
 * @tparam N number of bits equal to a power of two withing uint16 limit.
 */
template<uint16_t N>
class LargeInt {

    // Friend declarations:
    template<uint16_t M> friend class LargeInt; // This is "another brother".
    friend uint64_t to_decimal(const LargeInt<16>&);
    friend uint64_t to_decimal(const LargeInt<32>&);
    friend uint64_t to_decimal(const LargeInt<64>&);
    template<uint16_t M> friend void output_hex(std::ostream& os, const LargeInt<M>& number, uint16_t base);
    template<uint16_t M> friend void output_bin(std::ostream& os, const LargeInt<M>& number, uint16_t base);
    template<uint16_t M> friend std::pair<LargeInt<M/2>, LargeInt<M/2>> bz_algo::div_2n_1n(const LargeInt<M>& A, const LargeInt<M/2>& B);
    template<uint16_t M> friend std::pair<LargeInt<M/2>, LargeInt<M>> bz_algo::div_3n_2n(const LargeInt<M>& A_12, const LargeInt<M/2>& A_3, const LargeInt<M>& B);
    template<uint16_t M> friend std::pair<LargeInt<M>, LargeInt<M>> bz_algo::div_mod_bz(const LargeInt<M>& numerator, const LargeInt<M>& denominator);


    static_assert(N >= 8 , "LargeInt size must be at least one byte in size");
    static_assert((N & (N - 1)) == 0, "LargeInt size must be a power of 2 for recursive splitting");

    /// Stores two instances of LargeInt with half the size, to create the recursive data structure.
    LargeInt<N / 2> m_upper, m_lower;

    /// Temporal values used to make addition and subtraction easier.
    bool m_overflown, m_underflown;

    /// Remembers if instance is the upper or lower part of parent instance.
    const branch_side_t c_branch_side;

    /// For easier traversal in huge LargeInts, an instance stores a pointer to its parent.
    LargeInt<2 * N> *p_parent;

    /// Only used internal. Called by bigger LargeInts to parse the branching direction.
    LargeInt(uint8_t, branch_side_t);
    LargeInt(const LargeInt<N / 2> &);
    LargeInt(const LargeInt<N / 2> &, int);
    LargeInt(const LargeInt<N / 2> &,const LargeInt<N / 2> &);

    /**
     * @brief Called at the very end of the constructor. Needed to setup left, right and parent pointers.
     * @param parent point to the parent (very clear).
     * @param pp_last_leaf pointer to pointer to last leaf. Extra pointer needed for correct behaviour. After reading set pointer pointer to 'this'.
     */
    void initialize_pointers(LargeInt<2 * N> * = nullptr, LargeInt<8>** = nullptr);

    /// Efficient multiply by 10 + carry operator for reading strings. Faster then Karatsuba -> O(n)
    void multiply_by_ten(uint8_t carry = 0);

public:

    /** @constructDef */
    LargeInt();

    /** @constructInt*/
    LargeInt(uint8_t);

    /** @constructCopy */
    LargeInt(const LargeInt &);

    /** @constructStr */
    explicit LargeInt (const std::string&);

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
    LargeInt<N> operator+(const LargeInt<N> &) const;

    /** @subtract{new} */
    LargeInt<N> operator-(const LargeInt<N> &) const;

    /** @multiply{new}] */
    LargeInt<2*N> operator*(const LargeInt<N> &) const;

    /** @divide{quotient, new} */
    LargeInt<N> operator/(const LargeInt<N> &) const;

    /** @divide{remainder, new} */
    LargeInt<N> operator%(const LargeInt<N> &) const;

    /** @bitwiseNot{new} */
    LargeInt<N> operator~() const;

    /** @bitwise{AND, ands, new} */
    LargeInt<N> operator&(const LargeInt<N> &) const;

    /** @bitwise{OR, ors, new} */
    LargeInt<N> operator|(const LargeInt<N> &) const;

    /** @bitwise{XOR, xors, new} */
    LargeInt<N> operator^(const LargeInt<N> &) const;

    /** @bitshift{Left, left, new} */
    LargeInt<N> operator<<(uint16_t) const;

    /** @bitshift{Right, right, new} */
    LargeInt<N> operator>>(uint16_t) const;
    /** @} */

    // =================================================================================================================

    /**
     * @name Assignment Operators
     * @brief Standard mathematical and bitwise operations.
     * @{
     */
    /** @assign */
    LargeInt<N> &operator=(const LargeInt &);

    /** @add{this} */
    LargeInt<N> &operator+=(const LargeInt<N> &);

    /** @subtract{this} */
    LargeInt<N> &operator-=(const LargeInt<N> &);

    /** @multiply{this}] */
    LargeInt<N> &operator*=(const LargeInt<N> &);

    /** @divide{quotient, this} */
    LargeInt<N> &operator/=(const LargeInt<N> &);

    /** @divide{remainder, this} */
    LargeInt<N> &operator%=(const LargeInt<N> &);

    /** @bitwise{AND, ands, this} */
    LargeInt<N> &operator&=(const LargeInt<N> &);

    /** @bitwise{OR, ors, this} */
    LargeInt<N> &operator|=(const LargeInt<N> &);

    /** @bitwise{XOR, xors, this} */
    LargeInt<N> &operator^=(const LargeInt<N> &);

    /** @bitshift{Left, left, this} */
    LargeInt<N> &operator<<=(uint16_t);

    /** @bitshift{Right, right, this} */
    LargeInt<N> &operator>>=(uint16_t);
    /** @} */

    // =================================================================================================================

    /**
     * @name Comparison Operators
     * @brief Standard mathematical and bitwise operations.
     * @{
     */
    /** @compareEqual */
    bool operator==(const LargeInt<N> &) const;

    /** @compareSpaceship */
    std::strong_ordering operator<=>(const LargeInt<N> &) const;
    /** @} */

    // =================================================================================================================

    /**
     * @name In- / Decrement Operators
     * @brief Standard mathematical and bitwise operations.
     * @{
     */
    /** @prefix{increment, Increases} */
    LargeInt<N> &operator++();

    /** @prefix{decrement, Decreases} */
    LargeInt<N> &operator--();

    /** @postfix{increment, Increases} */
    LargeInt<N> operator++(int);

    /** @postfix{decrement, Decreases} */
    LargeInt<N> operator--(int);
    /** @} */

    /**
     * @brief type cast to uint64.
     * @return uint64 representation of this number.
     */
    explicit operator uint64_t() const {
        if(N > 64) {
            return m_lower.operator uint64_t;
        }
        switch(N) {
            case 64:
                const auto upper = m_upper.operator uint64_t;
                const auto lower = m_lower.operator uint64_t;
                return (upper << 32) | lower;
            case 32:
                const auto upper = m_upper.operator uint64_t;
                const auto lower = m_lower.operator uint64_t;
                return (upper << 16) | lower;
            case 16:
                const auto upper = m_upper.operator uint64_t;
                const auto lower = m_lower.operator uint64_t;
                return (upper << 8) | lower;
            default :
                // Should never reach this!
                return 0;
        }
    }
};

#include "details/member_core.hpp"
#include "operators/all_core.hpp"

#endif //LARGE_INT_CORE_HPP
