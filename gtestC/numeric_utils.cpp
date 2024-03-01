#include "numeric_utils.h"
#include <vector>
#include <numeric>
#include <iostream>

#ifdef __DISABLE_CODE__
int getTotalX(std::vector<int>& a, std::vector<int>& b) {
    int lcm_a = a[0];
    for (size_t i = 1; i < a.size(); ++i) {
        lcm_a = std::lcm(lcm_a, a[i]);
    }

    int gcd_b = b[0];
    for (size_t i = 1; i < b.size(); ++i) {
        gcd_b = std::gcd(gcd_b, b[i]);
    }

    int count = 0;
    for (int i = lcm_a, j = 2; i <= gcd_b; i = lcm_a * j, ++j) {
        if (gcd_b % i == 0) {
            ++count;
        }
    }

    return count;
}

#endif // __DISABLE_CODE__