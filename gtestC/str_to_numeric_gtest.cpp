#include "str_to_numeric.h"
#include <gtest/gtest.h>
#include <limits>
#include <iostream>

using namespace std;

class TestStr2Int: public testing::Test {};

TEST_F(TestStr2Int, PositiveIntegerOverflowIssues) {
    ASSERT_EQ(to_positive_integral<int>("2147483646"s), 2147483646);
    ASSERT_EQ(to_positive_integral<int>("2147483647"s), 2147483647);
    ASSERT_EQ(to_positive_integral<int>("2147483648"s), 214748364);
    ASSERT_EQ(to_positive_integral<char>("126"s), 126);
    ASSERT_EQ(to_positive_integral<char>("127"s), 127);
    ASSERT_EQ(to_positive_integral<char>("128"s), 12);

    // compile error's expected:
    // ASSERT_EQ(to_positive_integral<double>("123"s), 123);
}

TEST_F(TestStr2Int, NegativeIntegerOverflow) {
    ASSERT_EQ(to_integral<int64_t>("9223372036854775806"s), 9223372036854775806);
    ASSERT_EQ(to_integral<int64_t>("9223372036854775807"s), 9223372036854775807);
    ASSERT_EQ(to_integral<int64_t>("9223372036854775808"s), 922337203685477580);

    ASSERT_EQ(to_integral<int64_t>("-9223372036854775807"s), -9223372036854775807);
    // -9223372036854775807 - 1: to avaoid compilation warining
    ASSERT_EQ(to_integral<int64_t>("-9223372036854775808"s), -9223372036854775807 - 1);
    ASSERT_EQ(to_integral<int64_t>("-9223372036854775809"s), -922337203685477580);

    ASSERT_EQ(to_integral<int32_t>("2147483646"s), 2147483646);
    ASSERT_EQ(to_integral<int32_t>("2147483647"s), 2147483647);
    ASSERT_EQ(to_integral<int32_t>("2147483648"s), 214748364);

    ASSERT_EQ(to_integral<int32_t>("-2147483647"s), -2147483647);
    ASSERT_EQ(to_integral<int32_t>("-2147483648"s), -2147483648);
    ASSERT_EQ(to_integral<int32_t>("-2147483649"s), -214748364);

    ASSERT_EQ(to_integral<int8_t>("126"s), 126);
    ASSERT_EQ(to_integral<int8_t>("127"s), 127);
    ASSERT_EQ(to_integral<int8_t>("128"s), 12);

    ASSERT_EQ(to_integral<int8_t>("-127"s), -127);
    ASSERT_EQ(to_integral<int8_t>("-128"s), -128);
    ASSERT_EQ(to_integral<int8_t>("-129"s), -12);

    ASSERT_EQ(to_integral<uint32_t>("-123"s), 0);
    ASSERT_EQ(to_integral<uint32_t>("4294967294"s), 0xFFFFFFFE);
    ASSERT_EQ(to_integral<uint32_t>("4294967295"s), 0xFFFFFFFF);
    ASSERT_EQ(to_integral<uint32_t>("4294967296"s), 429496729);
}
