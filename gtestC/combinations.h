#ifndef _COMBINATIONS_H_
#define _COMBINATIONS_H_
#include "itertools.h"


template<typename T>
class Combinations
{
public:
    Combinations(const std::vector<T>& src, size_t len = 0):
        m_sources(src), m_len{len}, m_fin{false} {
        init();
    }

    Combinations(std::vector<T>&& src, size_t len = 0): m_len{len}, m_fin{false}
    {
        std::swap(m_sources, src);
        init();
    }

    operator bool() const {
        return !m_fin;
    }

    std::vector<T> next(void) {
        if (m_fin) { return {}; }

        if (m_indices.empty()) {
            if (m_len == m_sources.size()) {
                std::vector<T> combination(std::move(m_sources));
                disable();
                return combination;
            }

            m_indices.resize(m_len);
            auto cit = m_sources.cbegin();
            for (auto& index: m_indices) {
                index = cit;
                std::advance(cit, 1);
            }

            return iterators_to_values(m_indices);
        }

        auto src_it = std::prev(m_sources.cend());
        auto i = m_indices.size() - 1;
        for (; i >= 0; --i) {
            if (m_indices[i] != src_it) {
                std::advance(m_indices[i], 1);
                break;
            }
            std::advance(src_it, -1);
        }

        if (i == 0 and m_indices[i] == src_it) {
            auto&& combination = iterators_to_values(m_indices);
            disable();
            return combination;
        }

        for (i += 1; i < m_indices.size(); ++i) {
            m_indices[i] = std::next(m_indices[i-1]);
        }
        return iterators_to_values(m_indices);
    }

private:
    void disable(void) {
        m_sources.clear();
        m_indices.clear();
        m_fin = true;
    }

    void init(void) {
        if (m_len == 0) {
            m_len = m_sources.size();
        }
        if (m_sources.size() >= m_len) {
            m_indices.reserve(m_len);
        } else {
            disable();
        }
    }

    std::vector<T> m_sources;
    std::vector<typename std::vector<T>::const_iterator> m_indices;
    size_t m_len;
    bool m_fin;
};

template<typename Iterator>
class IteratorCombinations: public Combinations<Iterator> {
public:
    IteratorCombinations(Iterator first, Iterator last, size_t comb_len = 0):
            Combinations<Iterator>(get_range<Iterator>(first, last), comb_len) {
    }
};

#endif // _COMBINATIONS_H_