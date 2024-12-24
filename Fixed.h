#include <cstdint>
#include <iostream>
#include <type_traits>
#include <compare>

template <size_t N, size_t K, typename FAST = bool>
struct Fixed {
    static_assert(N <= 64, "Fixed<N, K> максимум 64 бита.");
    static_assert(N > 0, "Fixed<N, K> содержит хотя бы 1 бит.");
    static_assert(N > K, "Fixed<N, K> N < K, число всегда 0");
    static_assert(std::is_same_v<FAST, bool> ? ((N == 8) ? true : ((N == 16) ? true : ((N == 32) ? true : ((N == 64) ? true : false)))) : true, "Fixed<N, K> N не 8, 16, 32, 64.");

    using IntType = std::conditional_t<
            std::is_same_v<FAST, bool>,
            std::conditional_t<
                    (N == 8), int8_t,
                    std::conditional_t<
                            (N == 16), int16_t,
                            std::conditional_t<
                                    (N == 32), int32_t,
                                    std::conditional_t<
                                            (N == 64), int64_t,
                                            int64_t>
                            >
                    >
            >,
            std::conditional_t<
                    (N <= 8), int_fast8_t,
                    std::conditional_t<
                            (N <= 16), int_fast16_t,
                            std::conditional_t<
                                    (N <= 32), int_fast32_t,
                                    int_fast64_t
                            >
                    >
            >
    >;

    IntType value;

    Fixed() : value(0) {}

    friend std::ostream& operator<<(std::ostream& os, const Fixed& fp) {
        os << static_cast<double>(fp);
        return os;
    }

    constexpr Fixed(int32_t value)
            : value(static_cast<IntType>(value) << K) {
    }

    constexpr Fixed(float f)
            : value(static_cast<IntType>(f * (1ULL << K))) {}

    constexpr Fixed(double f)
            : value(static_cast<IntType>(f * (1ULL << K))) {}


    template <size_t M, size_t L, typename OtherTag>
    constexpr Fixed(const Fixed<M, L, OtherTag>& other) {
        double asDouble = static_cast<double>(other);
        value = static_cast<IntType>(asDouble * (1ULL << K));
    }

    template <size_t M, size_t L, typename OtherTag>
    Fixed& operator=(const Fixed<M, L, OtherTag>& other) {
        double asDouble = static_cast<double>(other);
        value = static_cast<IntType>(asDouble * (1ULL << K));
        return *this;
    }

public:
    explicit operator float() const {
        return static_cast<float>(value) / (1ULL << K);
    }

    explicit operator double() const {
        return static_cast<double>(value) / (1ULL << K);
    }

    auto operator<=>(const Fixed&) const = default;
    bool operator==(const Fixed&) const = default;

    Fixed operator+(const Fixed& other) const {
        Fixed result;
        result.value = this->value + other.value;
        return result;
    }

    Fixed operator-(const Fixed& other) const {
        Fixed result;
        result.value = this->value - other.value;
        return result;
    }

    Fixed operator*(const Fixed& other) const {
        Fixed result;
        if(N <= 16){
            int32_t temp = static_cast<int32_t>(value) * static_cast<int32_t>(other.value);
            result.value = static_cast<IntType>(temp >> K);
        }else{
            int64_t temp = static_cast<int64_t>(value) * static_cast<int64_t>(other.value);
            result.value = static_cast<IntType>(temp >> K);
        }
        return result;
    }

    Fixed operator/(const Fixed& other) const {
        Fixed result;
        if(N <= 16){
            int32_t temp = static_cast<int32_t>(value << K) / static_cast<int32_t>(other.value);
            result.value = static_cast<IntType>(temp);
        }else{
            int64_t temp = static_cast<int64_t>(value << K) / static_cast<int64_t>(other.value);
            result.value = static_cast<IntType>(temp);
        }
        return result;
    }

    Fixed& operator+=(const Fixed& other) {
        this->value += other.value;
        return *this;
    }

    Fixed& operator-=(const Fixed& other) {
        this->value -= other.value;
        return *this;
    }

    Fixed& operator*=(const Fixed& other) {
        *this = *this * other;
        return *this;
    }

    Fixed& operator/=(const Fixed& other) {
        *this = *this / other;
        return *this;
    }
};

template <size_t N, size_t K>
using FIXED = Fixed<N, K, bool>;

template <size_t N, size_t K>
using FAST_FIXED = Fixed<N, K, void>;

template <size_t N1, size_t K1, typename Tag1, size_t N2, size_t K2, typename Tag2>
constexpr bool operator<=(const Fixed<N1, K1, Tag1>& lhs, const Fixed<N2, K2, Tag2>& rhs) {
    return static_cast<double>(lhs) <= static_cast<double>(rhs);
}

template <size_t N1, size_t K1, typename Tag1, size_t N2, size_t K2, typename Tag2>
constexpr bool operator<(const Fixed<N1, K1, Tag1>& lhs, const Fixed<N2, K2, Tag2>& rhs) {
    return static_cast<double>(lhs) < static_cast<double>(rhs);
}

template <size_t N1, size_t K1, typename Tag1, size_t N2, size_t K2, typename Tag2>
constexpr bool operator>=(const Fixed<N1, K1, Tag1>& lhs, const Fixed<N2, K2, Tag2>& rhs) {
    return static_cast<double>(lhs) >= static_cast<double>(rhs);
}

template <size_t N1, size_t K1, typename Tag1, size_t N2, size_t K2, typename Tag2>
constexpr bool operator>(const Fixed<N1, K1, Tag1>& lhs, const Fixed<N2, K2, Tag2>& rhs) {
    return static_cast<double>(lhs) > static_cast<double>(rhs);
}

template <size_t N1, size_t K1, typename Tag1, size_t N2, size_t K2, typename Tag2>
constexpr bool operator==(const Fixed<N1, K1, Tag1>& lhs, const Fixed<N2, K2, Tag2>& rhs) {
    if constexpr (K1 > K2) {
        return lhs.value == (rhs.value << (K1 - K2));
    } else if constexpr (K2 > K1) {
        return (lhs.value << (K2 - K1)) == rhs.value;
    } else {
        return lhs.value == rhs.value;
    }
}

template <size_t N, size_t K, typename FAST>
Fixed<N, K, FAST> operator+(double lhs, const Fixed<N, K, FAST>& rhs) {
    return Fixed<N, K, FAST>(lhs + static_cast<double>(rhs));
}

template <size_t N, size_t K, typename FAST>
Fixed<N, K, FAST> operator-(double lhs, const Fixed<N, K, FAST>& rhs) {
    return Fixed<N, K, FAST>(lhs - static_cast<double>(rhs));
}

template <size_t N, size_t K, typename FAST>
Fixed<N, K, FAST> operator*(double lhs, const Fixed<N, K, FAST>& rhs) {
    return Fixed<N, K, FAST>(lhs * static_cast<double>(rhs));
}

template <size_t N, size_t K, typename FAST>
Fixed<N, K, FAST> operator*(const Fixed<N, K, FAST>& lhs, double rhs) {
    return Fixed<N, K, FAST>(static_cast<double>(lhs) * rhs);
}

template <size_t N, size_t K, typename FAST>
Fixed<N, K, FAST> operator/(const Fixed<N, K, FAST>& lhs, double rhs) {
    double result = static_cast<double>(lhs) / rhs;
    return Fixed<N, K, FAST>(result);
}

template <size_t N, size_t K, typename FAST>
Fixed<N, K, FAST> operator/(double lhs, const Fixed<N, K, FAST>& rhs) {
    double result = lhs / static_cast<double>(rhs);
    return Fixed<N, K, FAST>(result);
}

template <size_t N, size_t K, typename FAST>
constexpr bool operator>(const Fixed<N, K, FAST>& lhs, double rhs) {
    return static_cast<double>(lhs) > rhs;
}

template <size_t N, size_t K, typename FAST>
Fixed<N, K, FAST> operator+(const Fixed<N, K, FAST>& lhs, float rhs) {
    return Fixed<N, K, FAST>(static_cast<float>(lhs) + rhs);
}

template <size_t N, size_t K, typename FAST>
Fixed<N, K, FAST> operator-(const Fixed<N, K, FAST>& lhs, float rhs) {
    return Fixed<N, K, FAST>(static_cast<float>(lhs) - rhs);
}

template <size_t N, size_t K, typename FAST>
Fixed<N, K, FAST> operator*(const Fixed<N, K, FAST>& lhs, float rhs) {
    return Fixed<N, K, FAST>(static_cast<float>(lhs) * rhs);
}

template <size_t N, size_t K, typename FAST>
Fixed<N, K, FAST> operator/(const Fixed<N, K, FAST>& lhs, float rhs) {
    return Fixed<N, K, FAST>(static_cast<float>(lhs) / rhs);
}

template <size_t N, size_t K, typename FAST>
Fixed<N, K, FAST> operator+(float lhs, const Fixed<N, K, FAST>& rhs) {
    return Fixed<N, K, FAST>(lhs + static_cast<float>(rhs));
}

template <size_t N, size_t K, typename FAST>
Fixed<N, K, FAST> operator-(float lhs, const Fixed<N, K, FAST>& rhs) {
    return Fixed<N, K, FAST>(lhs - static_cast<float>(rhs));
}

template <size_t N, size_t K, typename FAST>
Fixed<N, K, FAST> operator*(float lhs, const Fixed<N, K, FAST>& rhs) {
    return Fixed<N, K, FAST>(lhs * static_cast<float>(rhs));
}

template <size_t N, size_t K, typename FAST>
Fixed<N, K, FAST> operator/(float lhs, const Fixed<N, K, FAST>& rhs) {
    return Fixed<N, K, FAST>(lhs / static_cast<float>(rhs));
}

template <size_t N, size_t K, typename FAST>
float operator+=(float& lhs, const Fixed<N, K, FAST>& rhs) {
    lhs += static_cast<float>(rhs);
    return lhs;
}

template<size_t N, size_t K, typename FAST>
double operator+=(double& lhs, const Fixed<N, K, FAST>& rhs) {
    lhs += static_cast<double>(rhs);
    return lhs;
}

template<size_t N, size_t K, typename FAST>
double operator-=(double& lhs, const Fixed<N, K, FAST>& rhs) {
    lhs -= static_cast<float>(rhs);
    return lhs;
}

template <size_t N, size_t K, typename FAST>
float operator-=(float& lhs, const Fixed<N, K, FAST>& rhs) {
    lhs -= static_cast<float>(rhs);
    return lhs;
}

template <size_t N, size_t K, typename FAST>
Fixed<N, K, FAST> operator+(const Fixed<N, K, FAST>& lhs, int rhs) {
    return lhs + Fixed<N, K, FAST>(rhs);
}

template <size_t N, size_t K, typename FAST>
Fixed<N, K, FAST> operator+(int lhs, const Fixed<N, K, FAST>& rhs) {
    return Fixed<N, K, FAST>(lhs) + rhs;
}

template <size_t N, size_t K, typename FAST>
Fixed<N, K, FAST> operator-(const Fixed<N, K, FAST>& lhs, int rhs) {
    return lhs - Fixed<N, K, FAST>(rhs);
}

template <size_t N, size_t K, typename FAST>
Fixed<N, K, FAST> operator-(int lhs, const Fixed<N, K, FAST>& rhs) {
    return Fixed<N, K, FAST>(lhs) - rhs;
}

template <size_t N, size_t K, typename FAST>
Fixed<N, K, FAST> operator*(const Fixed<N, K, FAST>& lhs, int rhs) {
    return lhs * Fixed<N, K, FAST>(rhs);
}

template <size_t N, size_t K, typename FAST>
Fixed<N, K, FAST> operator*(int lhs, const Fixed<N, K, FAST>& rhs) {
    return Fixed<N, K, FAST>(lhs) * rhs;
}

template <size_t N, size_t K, typename FAST>
Fixed<N, K, FAST> operator/(const Fixed<N, K, FAST>& lhs, int rhs) {
    return Fixed<N, K, FAST>(static_cast<double>(lhs) / rhs);
}

template <size_t N, size_t K, typename FAST>
Fixed<N, K, FAST> operator/(int lhs, const Fixed<N, K, FAST>& rhs) {
    return Fixed<N, K, FAST>(lhs / static_cast<double>(rhs));
}

template <size_t N, size_t K, typename FAST>
double operator-(double lhs, const Fixed<N, K, FAST>& rhs) {
    return lhs - static_cast<double>(rhs);
}

template <size_t N, size_t K, typename FAST>
double operator/(const Fixed<N, K, FAST>& lhs, double rhs) {
    return static_cast<double>(lhs) / rhs;
}

template <size_t N, size_t K, typename FAST>
double operator/(double lhs, const Fixed<N, K, FAST>& rhs) {
    return lhs / static_cast<double>(rhs);
}

template <size_t N, size_t K, typename FAST>
inline bool operator<=(const Fixed<N, K, FAST>& lhs, double rhs) {
    return static_cast<double>(lhs) <= rhs;
}

template <size_t N, size_t K, typename FAST>
inline bool operator<=(double lhs, const Fixed<N, K, FAST>& rhs) {
    return lhs <= static_cast<double>(rhs);
}