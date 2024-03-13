#ifndef _STR_TO_NUMERIC_H_
#define _STR_TO_NUMERIC_H_
#include <string>
#include <type_traits>

template<typename T>
constexpr T integral_max(void) {
    static_assert(std::is_integral<T>::value, "Only integral types allowed.");
    if constexpr(std::is_signed<T>::value) {
        return T(~(T(0x01) << ((sizeof(T) << 3) - 1)));
    } else {
        return T(~(T{0}));
    }
}

template<typename T>
T to_positive_integral(const std::string& str) {
    static_assert(std::is_integral<T>::value, "Only integral types allowed.");
    constexpr T MAX_INT = integral_max<T>();
    T digit{0}, result{0};

    for (std::string::size_type i{0}; i < str.size(); ++i) {
        digit = str[i] - '0';
        if (digit < 0 or digit > 9) {
            break;
        }

        if (digit > MAX_INT - result*10) {
            break;
        }

        result = 10 * result + digit;
        if (result > MAX_INT/10) {
            break;
        }
    }
    return result;
}

template<typename T>
T to_integral(const std::string& str) {
    static_assert(std::is_integral<T>::value, "Only integral types allowed.");
    constexpr T MAX_INT = integral_max<T>();
    constexpr int MAX_DIGITS = [=]{
        int n_digit{0};
        for (T temp{MAX_INT}; temp > 0; temp /= 10, ++n_digit);
        return n_digit;
    }();

    T digit{0}, result{0}, sign{1};
    std::string::size_type i{0};

    if (str[i] == '-') {
        if constexpr(! std::is_signed<T>::value) {
            return 0;
        } else {
            sign = -1;
            ++i;
        }
    }

    for (int ndigit{1}; i < str.size(); ++i, ++ndigit) {
        digit = str[i] - '0';
        if (digit < 0 or digit > 9) {
            break;
        }

        if (ndigit < MAX_DIGITS) {
            result = 10 * result + digit;
            continue;
        }

        /*
         * In case of overflow, handle the last digit separately.
         * Notice that negative integral has one more value than the positive.
        */
        auto max_digit = sign > 0? MAX_INT-result*10: MAX_INT-result*10+1;
        if (digit > max_digit) {
            break;
        }
        return sign * result * 10 + sign * digit;
    }

    return sign * result;
}

#endif // _STR_TO_NUMERIC_H_
