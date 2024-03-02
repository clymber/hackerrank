#include "combinations.h"
#include <gtest/gtest.h>
#include <vector>
#include <iostream>

class TestCombinate: public testing::Test {};

TEST_F(TestCombinate, CombinationWithAllElements) {
    std::vector<int> data{1, 2, 3, 4};
    Combinations test(data);

    ASSERT_TRUE(test);
    ASSERT_EQ(test.next(), data);
    ASSERT_FALSE(test);
}

TEST_F(TestCombinate, CombinationsWithPartialElements) {
    std::vector<int> data{1, 2, 3, 4, 5};
    Combinations test(std::move(data), 3);

    ASSERT_TRUE(test);
    ASSERT_EQ(test.next(), std::vector<int>({1, 2, 3}));
    ASSERT_EQ(test.next(), std::vector<int>({1, 2, 4}));
    ASSERT_EQ(test.next(), std::vector<int>({1, 2, 5}));
    ASSERT_EQ(test.next(), std::vector<int>({1, 3, 4}));
    ASSERT_EQ(test.next(), std::vector<int>({1, 3, 5}));
    ASSERT_EQ(test.next(), std::vector<int>({1, 4, 5}));
    ASSERT_EQ(test.next(), std::vector<int>({2, 3, 4}));
    ASSERT_EQ(test.next(), std::vector<int>({2, 3, 5}));
    ASSERT_EQ(test.next(), std::vector<int>({2, 4, 5}));
    ASSERT_EQ(test.next(), std::vector<int>({3, 4, 5}));
    ASSERT_FALSE(test);
}

class TestIteratorCombinations: public testing::Test {};

TEST_F(TestIteratorCombinations, foo) {
    std::set<int> data{1, 2, 3, 4, 5};
    IteratorCombinations test(data.begin(), data.end(), 3);

    ASSERT_TRUE(test);
    ASSERT_EQ(iterators_to_values(test.next()), std::vector<int>({1, 2, 3}));
    ASSERT_EQ(iterators_to_values(test.next()), std::vector<int>({1, 2, 4}));
    ASSERT_EQ(iterators_to_values(test.next()), std::vector<int>({1, 2, 5}));
    ASSERT_EQ(iterators_to_values(test.next()), std::vector<int>({1, 3, 4}));
    ASSERT_EQ(iterators_to_values(test.next()), std::vector<int>({1, 3, 5}));
    ASSERT_EQ(iterators_to_values(test.next()), std::vector<int>({1, 4, 5}));
    ASSERT_EQ(iterators_to_values(test.next()), std::vector<int>({2, 3, 4}));
    ASSERT_EQ(iterators_to_values(test.next()), std::vector<int>({2, 3, 5}));
    ASSERT_EQ(iterators_to_values(test.next()), std::vector<int>({2, 4, 5}));
    ASSERT_EQ(iterators_to_values(test.next()), std::vector<int>({3, 4, 5}));
    ASSERT_FALSE(test);
}

TEST_F(TestIteratorCombinations, bar) {
    int data[5] = {1, 2, 3, 4, 5};
    IteratorCombinations test(data, data+5, 3);

    ASSERT_TRUE(test);
    ASSERT_EQ(pointers_to_values(test.next()), std::vector<int>({1, 2, 3}));
    ASSERT_EQ(pointers_to_values(test.next()), std::vector<int>({1, 2, 4}));
    ASSERT_EQ(pointers_to_values(test.next()), std::vector<int>({1, 2, 5}));
    ASSERT_EQ(pointers_to_values(test.next()), std::vector<int>({1, 3, 4}));
    ASSERT_EQ(pointers_to_values(test.next()), std::vector<int>({1, 3, 5}));
    ASSERT_EQ(pointers_to_values(test.next()), std::vector<int>({1, 4, 5}));
    ASSERT_EQ(pointers_to_values(test.next()), std::vector<int>({2, 3, 4}));
    ASSERT_EQ(pointers_to_values(test.next()), std::vector<int>({2, 3, 5}));
    ASSERT_EQ(pointers_to_values(test.next()), std::vector<int>({2, 4, 5}));
    ASSERT_EQ(pointers_to_values(test.next()), std::vector<int>({3, 4, 5}));
    ASSERT_FALSE(test);
}
