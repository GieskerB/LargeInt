#ifndef LARGEINT_DEBUG_PRINT_HPP
#define LARGEINT_DEBUG_PRINT_HPP

inline std::ostream &operator<<(std::ostream &os, const LargeInt<8> &large_int) {
    os << static_cast<unsigned>(+large_int.m_value);
    return os;
}

inline std::ostream &operator<<(std::ostream &os, const LargeInt<16> &large_int) {
    os << static_cast<unsigned>((+large_int.m_upper.m_value << 8) + +large_int.m_lower.m_value);
    return os;
}

inline std::ostream &operator<<(std::ostream &os, const LargeInt<32> &large_int) {
    os << static_cast<unsigned>((+large_int.m_upper.m_upper.m_value << 24) + (+large_int.m_upper.m_lower.m_value << 16) +
                                (+large_int.m_lower.m_upper.m_value << 8) + +large_int.m_lower.m_lower.m_value);
    return os;
}

inline std::ostream &operator<<(std::ostream &os, const LargeInt<64> &large_int) {
    os << (static_cast<unsigned long long>(large_int.m_upper.m_upper.m_upper.m_value) << 56) +
            (static_cast<unsigned long long>(large_int.m_upper.m_upper.m_lower.m_value) << 48) +
            (static_cast<unsigned long long>(large_int.m_upper.m_lower.m_upper.m_value) << 40) +
            (static_cast<unsigned long long>(large_int.m_lower.m_upper.m_lower.m_value) << 32) +
            (+large_int.m_lower.m_upper.m_upper.m_value << 24) +
            (+large_int.m_lower.m_upper.m_lower.m_value << 16) +
            (+large_int.m_lower.m_lower.m_upper.m_value << 8) +
            +large_int.m_lower.m_lower.m_lower.m_value;
    return os;
}

#endif //LARGEINT_DEBUG_PRINT_HPP
