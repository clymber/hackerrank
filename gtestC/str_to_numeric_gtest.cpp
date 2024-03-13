#include "str_to_numeric.h"
#include <gtest/gtest.h>
#include <limits>
#include <iostream>

using namespace std;

class TestStrToIntegral: public testing::Test {};

TEST_F(TestStrToIntegral, SkipLeadingWhiteSpaces) {
    ASSERT_EQ(to_integral<int8_t>(" 123"), 123);
    ASSERT_EQ(to_integral<int16_t>("\n123"), 123);
    ASSERT_EQ(to_integral<int32_t>("\t123"), 123);
    ASSERT_EQ(to_integral<int64_t>("\v123"), 123);
    ASSERT_EQ(to_integral<uint32_t>(" \n\t\v123"), 123);
}

TEST_F(TestStrToIntegral, SignedTypesSupportNegative) {
    ASSERT_EQ(to_integral<int8_t>(" -123"), -123);
    ASSERT_EQ(to_integral<int16_t>("\n-123"), -123);
    ASSERT_EQ(to_integral<int32_t>("\t-123"), -123);
    ASSERT_EQ(to_integral<int64_t>("\v-123"), -123);
    ASSERT_EQ(to_integral<int32_t>(" \n\t\v-123"), -123);
}

TEST_F(TestStrToIntegral, UnsignedTypesNotSupportNegative) {
    ASSERT_EQ(to_integral<uint8_t>(" -123"), 0);
    ASSERT_EQ(to_integral<uint16_t>("\n-123"), 0);
    ASSERT_EQ(to_integral<uint32_t>("\t-123"), 0);
    ASSERT_EQ(to_integral<uint64_t>("\v-123"), 0);
    ASSERT_EQ(to_integral<uint32_t>(" \n\t\v-123"), 0);
}

TEST_F(TestStrToIntegral, InCasesOfOverflow) {
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

    ASSERT_EQ(to_integral<uint32_t>("4294967294"s), 0xFFFFFFFE);
    ASSERT_EQ(to_integral<uint32_t>("4294967295"s), 0xFFFFFFFF);
    ASSERT_EQ(to_integral<uint32_t>("4294967296"s), 429496729);
}
