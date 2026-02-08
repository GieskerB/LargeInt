#ifndef LARGEINT_OUTPUT_HPP
#define LARGEINT_OUTPUT_HPP

#include <cstdint>
#include <ostream>

#include "../large_int_core.hpp"
#include "../large_int_8.hpp"

#include <iomanip>

// template<uint16_t N>
// class LargeInt;
//
// inline std::ostream &operator<<(std::ostream &os, const LargeInt<8> &large_int) {
//     os << static_cast<unsigned>(+large_int.m_value);
//     return os;
// }
//
// inline std::ostream &operator<<(std::ostream &os, const LargeInt<16> &large_int) {
//     os << static_cast<unsigned>((+large_int.m_upper.m_value << 8) + +large_int.m_lower.m_value);
//     return os;
// }
//
// inline std::ostream &operator<<(std::ostream &os, const LargeInt<32> &large_int) {
//     os << static_cast<unsigned>((+large_int.m_upper.m_upper.m_value << 24) + (+large_int.m_upper.m_lower.m_value << 16) +
//                                 (+large_int.m_lower.m_upper.m_value << 8) + +large_int.m_lower.m_lower.m_value);
//     return os;
// }
//
// inline std::ostream &operator<<(std::ostream &os, const LargeInt<64> &large_int) {
//     os << (static_cast<unsigned long long>(large_int.m_upper.m_upper.m_upper.m_value) << 56) +
//             (static_cast<unsigned long long>(large_int.m_upper.m_upper.m_lower.m_value) << 48) +
//             (static_cast<unsigned long long>(large_int.m_upper.m_lower.m_upper.m_value) << 40) +
//             (static_cast<unsigned long long>(large_int.m_lower.m_upper.m_lower.m_value) << 32) +
//             (+large_int.m_lower.m_upper.m_upper.m_value << 24) +
//             (+large_int.m_lower.m_upper.m_lower.m_value << 16) +
//             (+large_int.m_lower.m_lower.m_upper.m_value << 8) +
//             +large_int.m_lower.m_lower.m_lower.m_value;
//     return os;
// }

#endif //LARGEINT_OUTPUT_HPP