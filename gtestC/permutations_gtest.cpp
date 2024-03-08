#include "permutations.h"
#include <vector>
#include <set>
#include <deque>
#include <list>
#include <iterator>
#include <gtest/gtest.h>

class TestPermutations: public testing::Test {};

TEST_F(TestPermutations, InvalidInput) {
    Permutations empty_input(std::vector<int>(), 0);
    std::vector<int> result;
    ASSERT_FALSE(empty_input);
    ASSERT_FALSE(empty_input.next(std::back_inserter(result)));

    Permutations out_of_range(std::vector<int>{1, 2, 3}, 4);
    ASSERT_FALSE(out_of_range);
    ASSERT_FALSE(out_of_range.next(std::back_inserter(result)));
}

TEST_F(TestPermutations, OneDataInput) {
    Permutations one_data(std::vector<int>{666});
    std::set<int> result;
    std::set<int> expect{666};

    ASSERT_TRUE(one_data);
    ASSERT_TRUE(one_data.next(std::inserter(result, result.end())));
    ASSERT_EQ(result, expect);
    ASSERT_FALSE(one_data);
}

TEST_F(TestPermutations, DefaultPermuteLengthZero) {
    Permutations default_permu(std::vector<int>{1, 2, 3});
    std::deque<int> result;
    std::deque<int> expect;

    ASSERT_TRUE(default_permu);
    ASSERT_TRUE(default_permu.next(std::back_inserter(result)));
    expect = std::deque<int>{1, 2, 3};
    ASSERT_EQ(result, expect);

    ASSERT_TRUE(default_permu);
    ASSERT_TRUE(default_permu.next(result.begin()));
    expect = std::deque<int>{1, 3, 2};
    ASSERT_EQ(result, expect);

    ASSERT_TRUE(default_permu.next(result.begin()));
    expect = std::deque<int>{2, 1, 3};
    ASSERT_EQ(result, expect);

    ASSERT_TRUE(default_permu.next(result.begin()));
    expect = std::deque<int>{2, 3, 1};
    ASSERT_EQ(result, expect);

    ASSERT_TRUE(default_permu.next(result.begin()));
    expect = std::deque<int>{3, 1, 2};
    ASSERT_EQ(result, expect);

    ASSERT_TRUE(default_permu.next(result.begin()));
    expect = std::deque<int>{3, 2, 1};
    ASSERT_EQ(result, expect);

    ASSERT_FALSE(default_permu);
    ASSERT_FALSE(default_permu.next(result.begin()));
}


TEST_F(TestPermutations, PartialLenthPermute) {
    Permutations default_permu(std::vector<int>{1, 2, 3}, 2);
    std::deque<int> result;
    std::deque<int> expect;

    ASSERT_TRUE(default_permu);
    ASSERT_TRUE(default_permu.next(std::back_inserter(result)));
    expect = std::deque<int>{1, 2};
    ASSERT_EQ(result, expect);

    ASSERT_TRUE(default_permu);
    ASSERT_TRUE(default_permu.next(result.begin()));
    expect = std::deque<int>{1, 3};
    ASSERT_EQ(result, expect);

    ASSERT_TRUE(default_permu.next(result.begin()));
    expect = std::deque<int>{2, 1};
    ASSERT_EQ(result, expect);

    ASSERT_TRUE(default_permu.next(result.begin()));
    expect = std::deque<int>{2, 3};
    ASSERT_EQ(result, expect);

    ASSERT_TRUE(default_permu.next(result.begin()));
    expect = std::deque<int>{3, 1};
    ASSERT_EQ(result, expect);

    ASSERT_TRUE(default_permu.next(result.begin()));
    expect = std::deque<int>{3, 2};
    ASSERT_EQ(result, expect);

    ASSERT_FALSE(default_permu);
    ASSERT_FALSE(default_permu.next(result.begin()));
}

TEST_F(TestPermutations, OneElementPermute) {
    Permutations default_permu(std::vector<int>{1, 2, 3}, 1);
    std::deque<int> result;
    std::deque<int> expect;

    ASSERT_TRUE(default_permu);
    ASSERT_TRUE(default_permu.next(std::back_inserter(result)));
    expect = std::deque<int>{1};
    ASSERT_EQ(result, expect);

    ASSERT_TRUE(default_permu);
    ASSERT_TRUE(default_permu.next(result.begin()));
    expect = std::deque<int>{2};
    ASSERT_EQ(result, expect);

    ASSERT_TRUE(default_permu.next(result.begin()));
    expect = std::deque<int>{3};
    ASSERT_EQ(result, expect);

    ASSERT_FALSE(default_permu);
    ASSERT_FALSE(default_permu.next(result.begin()));
}

int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n-1);
}

TEST_F(TestPermutations, PermutationsNumber) {
    std::vector<int> data{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Permutations test(data, 5);
    std::list<int> permutation(5);
    int n_permutation = 0;

    while (test.next(permutation.begin())) { n_permutation += 1; }
    ASSERT_EQ(n_permutation, factorial(10)/factorial(10 - 5));

    test = Permutations(data, 3);
    n_permutation = 0;

    while (test.next(permutation.begin())) { n_permutation += 1; }
    ASSERT_EQ(n_permutation, factorial(10)/factorial(10 - 3));
}