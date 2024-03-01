#include "numeric_utils.h"
#include <gtest/gtest.h>
#include <array>

/*
 * Test range_lcm(): Least Common Multiple of a range of numeric elements.
*/
class TestRangeLcm: public testing::Test {};

TEST_F(TestRangeLcm, TwoElements) {
    std::array<int, 2> range{30, 42};
    auto lcm = range_lcm(range.begin()+1, range.end(), range.front());
    ASSERT_EQ(lcm, 210);
}

TEST_F(TestRangeLcm, MultipleElements) {
    std::vector<long> range{2, 3, 5, 30, 42, 165};
    auto lcm = range_lcm(range.begin()+1, range.end(), range.front());
    ASSERT_EQ(lcm, 2310);
}


/*
 * Test range_gcd(): Greatest Common Divisor of a range of numeric elements.
*/
class TestRangeGcd: public testing::Test {};

TEST_F(TestRangeGcd, TwoElements) {
    std::array<unsigned int, 5> range{9, 15, 45, 21, 11};

    auto gcd = range_gcd(range.begin(), range.begin()+1, range[1]);
    ASSERT_EQ(gcd, 3);

    gcd = range_gcd(range.begin()+1, range.begin()+2, range[2]);
    ASSERT_EQ(gcd, 15);

    gcd = range_gcd(range.begin()+2, range.begin()+3, range[3]);
    ASSERT_EQ(gcd, std::gcd(45, 21));

    gcd = range_gcd(range.begin()+3, range.begin()+4, range[4]);
    ASSERT_EQ(gcd, std::gcd(21, 11));
}

TEST_F(TestRangeGcd, MultipuleElements) {
    std::set<int> range{9, 15, 45, 75};
    auto gcd = range_gcd(range.begin(), range.end(), 90);
    ASSERT_EQ(gcd, 3);
}


class TestCommonDivisors: public testing::Test {};

TEST_F(TestCommonDivisors, TwoNumbers) {
    auto cds = common_divisors<int>(2*3*5, 3*5*7);
    std::set<int> expect{1, 3, 5, 15};
    ASSERT_EQ(cds, expect);
}

TEST_F(TestCommonDivisors, MultipleNumbers) {
    std::array<int, 5> range{1000, 25, 50, 100, 200};
    auto cds = common_divisors(range.begin(), range.end(), 75);
    std::set<int> expect{1, 5, 25};
    ASSERT_EQ(cds, expect);
}

TEST_F(TestCommonDivisors, OneNumber) {
    std::vector<int> range{};
    auto cds = common_divisors(range.begin(), range.end(), 15);
    std::set<int> expect{1, 3, 5, 15};
    ASSERT_EQ(cds, expect);
}
