#ifndef LARGEINT_OUTPUT_HPP
#define LARGEINT_OUTPUT_HPP

#include <cstdint>
#include <ostream>
#include <iomanip>
#include <bitset>

#include "../large_int_core.hpp"
#include "../large_int_8.hpp"


inline uint64_t to_decimal(const LargeInt<8>& number) {
    return number.m_value;
}
inline uint64_t to_decimal(const LargeInt<16>& number) {
    return (to_decimal(number.m_upper) << 8) | to_decimal(number.m_lower);
}
inline uint64_t to_decimal(const LargeInt<32>& number) {
    return (to_decimal(number.m_upper) << 16) | to_decimal(number.m_lower);
}
inline uint64_t to_decimal(const LargeInt<64>& number) {
    return (to_decimal(number.m_upper) << 32) | to_decimal(number.m_lower);
}
template<uint16_t N> uint64_t to_decimal(const LargeInt<N>& number) {return 0;}


inline void output_bin(std::ostream& os, const LargeInt<8>& number, const uint16_t base) {
    os << std::bitset<8>(+number.m_value);
    if (base == 8) {
        os << " - [" << to_decimal(number)<< "]";
    }
}

template<uint16_t N> void output_bin(std::ostream& os, const LargeInt<N>& number, const uint16_t base) {
    output_bin(os, number.m_upper, base);
    output_bin(os, number.m_lower, base);
    if (N == base and N <= 64) {
        os << " - [" << to_decimal(number)<< "]";
    }
}

inline void output_hex(std::ostream& os, const LargeInt<8>& number, const uint16_t base) {
    os << std::hex << std::setw(2) << std::setfill('0') << +number.m_value << std::dec;
    if (base == 8) {
        os << " - [" << to_decimal(number)<< "]";
    }
}

template<uint16_t N> void output_hex(std::ostream& os, const LargeInt<N>& number, const uint16_t base) {
    output_hex(os, number.m_upper, base);
    output_hex(os, number.m_lower, base);
    if (N == base and N <= 64) {
        os << " - [" << to_decimal(number)<< "]";
    }
}

template<uint16_t N> std::ostream &operator<<(std::ostream& os, const LargeInt<N>& number) {
#ifdef DEBUG_PRINT
    #ifdef BINARY_PRINT
        output_bin(os, number, N);
    #else
        output_hex(os, number, N);
    #endif
#else
    static_assert(N <= 64, "Can only print numbers with less or eqauls to 64 bits");
    os << to_decimal(number);
#endif

    return os;
}

#endif //LARGEINT_OUTPUT_HPP