#pragma once
#include<vector>

template <typename T> class Stats {
    std::vector<T> m_vals;
    int m_runs;
    public:
        Stats(int runs);
        void run_func(T(*func)());
        double mean();
        double median();
        double std_dev();
        double variance();
        std::vector<T> get_vals();
};
