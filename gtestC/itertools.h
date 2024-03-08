#ifndef _ITERATOR_TOOLS_H_
#define _ITERATOR_TOOLS_H_
#include <algorithm>
#include <cstddef>
#include <vector>
#include <utility>
#include <iostream>

template<typename T>
std::vector<T> get_range(T first, T last) {
    std::vector<T> range;
    for (; first != last; std::advance(first, 1)) {
        range.push_back(first);
    }
    return range;
}

template<typename Iterator>
auto iterators_to_values(std::vector<Iterator>&& iterators) {
    std::vector<typename Iterator::value_type> values;
    for (auto i: iterators) {
        values.push_back(*i);
    }
    return values;
}

template<typename Iterator>
auto iterators_to_values(const std::vector<Iterator>& iterators) {
    std::vector<typename Iterator::value_type> values;
    for (auto i: iterators) {
        values.push_back(*i);
    }
    return values;
}

template<typename T>
std::vector<T> pointers_to_values(const std::vector<T*> pointers) {
    std::vector<T> result;

    for (auto i: pointers) {
        result.push_back(*i);
    }

    return result;
}

#include "combinations.h"
#include "permutations.h"
#endif //_ITERATOR_TOOLS_H_
