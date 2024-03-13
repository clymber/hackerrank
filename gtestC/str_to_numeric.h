#ifndef _STR_TO_NUMERIC_H_
#define _STR_TO_NUMERIC_H_
#include <string>
#include <type_traits>

template<typename T>
constexpr T max_integral_value(void) {
    static_assert(std::is_integral<T>::value, "Only integral types allowed.");
    if constexpr(std::is_signed<T>::value) {
        return T(~(T(0x01) << ((sizeof(T) << 3) - 1)));
    } else {
        return T(~(T{0}));
    }
}

template<typename T>
constexpr size_t max_decimal_digits(void) {
    size_t n_digit{0};
    for (T temp{max_integral_value<T>()}; temp > 0; temp /= 10, ++n_digit);
    return n_digit;
}

template<typename T>
T to_integral(const std::string& str) {
    constexpr T MAX_INT = max_integral_value<T>();
    constexpr size_t MAX_DIGITS = max_decimal_digits<T>();
    T digit{0}, result{0}, sign{1};
    std::string::size_type i{0};

    // skip leading spaces
    while (str[i] == ' ' or str[i] == '\n' or str[i] == '\t' or str[i] == '\v'){
        ++i;
    }

    // support negative value for signed types only
    if constexpr(std::is_signed<T>::value) {
        if (str[i] == '-') {
            sign = -1;
            ++i;
        }
    }

    // process the decimal characters
    for (size_t ndigit{0}; i < str.size(); ++i) {
        digit = str[i] - '0';
        if (digit < 0 or digit > 9) {
            break;
        }

        if (++ndigit < MAX_DIGITS) {
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
