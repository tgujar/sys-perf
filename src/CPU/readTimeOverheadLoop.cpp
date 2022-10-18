// Experiment to measure overhead of using a loop

#include <iostream>
#include <chrono>
#include <unistd.h>
#include <sched.h>
#include "timer.hpp"
#include "stats.hpp"
#include "proc.hpp"
using namespace std;

const int N_RUNS = 10;
const int N_ITERATIONS = 10000;

// Returns number of cycles
double readTimeOverheadInCycles() {
    Timer t;
    t.begin();
    for(int i = 0; i < N_ITERATIONS; i++);
    t.end();
    return (double) t.diff() / N_ITERATIONS;
}

// Returns time in microseconds
double readTimeOverheadInMicroSec() {
    Timer t;
    t.begin();
    for(int i = 0; i < N_ITERATIONS; i++);
    t.end();
    return t.time_diff_micro() / N_ITERATIONS;
}


int main() {
    Stats<double> s(N_RUNS);
    use_cores(vector<int> {0}); // force process to use only single core

    s.run_func(readTimeOverheadInCycles);
    cout << "Mean : " << s.mean() << " cycles" << endl;
    cout << "Variance : " << s.variance() << " cycles" << endl;
    cout << "Median : " << s.median() << " cycles" << endl;
    cout << "Std dev : " << s.std_dev() << " cycles" << endl;

    s.reset_vals();
    s.run_func(readTimeOverheadInMicroSec);
    cout << "Mean : " << s.mean() << " us" << endl;
    cout << "Variance : " << s.variance() << " us" << endl;
    cout << "Median : " << s.median() << " us" << endl;
    cout << "Std dev : " << s.std_dev() << " us" << endl;
}