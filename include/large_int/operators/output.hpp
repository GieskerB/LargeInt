#ifndef LARGEINT_OUTPUT_HPP
#define LARGEINT_OUTPUT_HPP

#include <cstdint>
#include <ostream>

#include "../large_int_core.hpp"
#include "../large_int_8.hpp"

#include <iomanip>

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
    output_hex(os, number, N);
    return os;
}

#endif //LARGEINT_OUTPUT_HPP