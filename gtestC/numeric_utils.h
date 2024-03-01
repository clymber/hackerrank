#ifndef _NUMERIC_UTILS_H_
#define _NUMERIC_UTILS_H_
#include <numeric>
#include <set>

/*
 * Least Common Multiple of a range of numeric elements.
*/
template<typename InputIterator, typename T>
constexpr T range_lcm(InputIterator first, InputIterator last, T init) {
    return std::accumulate(first, last, init, std::lcm<T,T>);
}

/*
 * Greatest Common Divisor of a range of numeric elements.
*/
template<typename InputIterator, typename T>
constexpr T range_gcd(InputIterator first, InputIterator last, T init) {
    return std::accumulate(first, last, init, std::gcd<T,T>);
}

/*
 * Get a set of common divisors of @lhs and @rhs.
*/
template<typename T>
std::set<T> common_divisors(const T& lhs, const T& rhs)
{
    std::set<T> result{1};
    for (T divisor = std::min(lhs, rhs); divisor > 1; --divisor) {
        if (lhs%divisor == 0 and rhs%divisor == 0) {
            result.insert(divisor);
        }
    }
    return result;
}

/*
 * Get common divisors of a range of numerbers.
*/
template<typename InputIterator, typename T>
std::set<T> common_divisors(InputIterator first, InputIterator last, T init) {
    if (first == last) {
        return common_divisors(init, init);
    }

    std::set<T> result = common_divisors<T>(init, *first);
    while (++first != last) {
        if (result.size() == 1) {
            return result;
        }

        auto it = result.begin();
        while (it != result.end()) {
            if (*first % *it != 0) {
                it = result.erase(it);
            } else {
                ++it;
            }
        }
    }
    return result;
}

#endif // _NUMERIC_UTILS_H_