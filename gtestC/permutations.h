#ifndef _PERMUTATIONS_H_
#define _PERMUTATIONS_H_
#include "itertools.h"
#include <vector>
#include <iostream>

template <typename T>
class Permutations {
public:
    Permutations(const std::vector<T>& src, size_t len = 0):
        m_data(src), m_len(len) {
        init();
    }

    Permutations(std::vector<T>&& src, size_t len = 0): m_len(len) {
        std::swap(src, m_data);
        init();
    }

    Permutations(const Permutations&) = default;
    Permutations(Permutations&&) = default;
    Permutations& operator=(const Permutations&) = default;
    Permutations& operator=(Permutations&&) = default;
    operator bool() const { return !is_done(); }

    template<typename OutputIterator>
    bool next(OutputIterator first) {
        if (is_done()) {
            return false;
        }
        std::copy_n(m_data.cbegin(), m_len, first); // output one permutation

        auto pos = m_counters.size() - 1;
        m_counters[pos] -= 1;

        if (m_counters[pos] == 0) {
            while (m_counters[pos] == 0) {
                if (pos == 0 or m_counters[pos-1] == 0) {
                    disable();
                    return true;
                }
                m_counters[--pos] -= 1;
            }

            for (auto i = pos + 1; i < m_counters.size(); ++i) {
                m_counters[i] = m_data.size() - i;
            }
            std::sort(m_data.begin() + pos + 1, m_data.end());
        }

        auto pos2 = m_data.size() - m_counters[pos];
        std::swap(m_data[pos], m_data[pos2]);
        return true;
    }
private:
    void init(void) {
        if (m_len == 0) {
            m_len = m_data.size();
        }
        if (m_len <= 0 or m_len > m_data.size()) {
            disable();
            return;
        }
        for (size_t i = 0; i < m_len; ++i) {
            m_counters.push_back(m_data.size() - i);
        }
    }
    void disable(void) {
        m_data.clear();
        m_counters.clear();
    }
    bool is_done(void) const {
        return m_counters.empty();;
    }

    std::vector<T> m_data;
    std::vector<size_t> m_counters;
    size_t m_len;
};

#endif // _PERMUTATIONS_H_
