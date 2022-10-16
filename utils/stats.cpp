#include <vector>
#include <cmath>
#include "stats.hpp"

using namespace std;
template <typename T> Stats<T>::Stats(int n) : m_runs(n) {}

template <typename T> void Stats<T>::run_func( T(*func)()) {
    for (int i = 0; i < m_runs; i++) {
        m_vals.push_back(func());
    }
}

template <typename T> double Stats<T>::mean() {
    if (m_vals.size() == 0) {
        return 0;
    }

    T sum = 0;
    for (auto &v: m_vals) {
        sum += v;
    }
    return sum / m_vals.size();
}

template <typename T> double Stats<T>::std_dev() {
    return sqrt(variance());
}

template <typename T> double Stats<T>::variance() {
    if (m_vals.size() == 0) {
        return 0;
    }
    double m = mean();
    double sum = 0;
    for (auto &v: m_vals) {
        sum += pow(v - m, 2);
    }
    return sqrt(sum / m_vals.size());
}


// Explicit template instantiation
template class Stats<double>;
template class Stats<int>;