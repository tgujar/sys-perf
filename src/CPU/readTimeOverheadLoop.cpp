// Experiment to measure overhead of using a loop

#include <iostream>
#include <chrono>
#include <unistd.h>
#include <sched.h>
#include "timer.hpp"
#include "stats.hpp"
#include "proc.hpp"
using namespace std;

const int N_RUNS = 100;
const int N_ITERATIONS = 10000000;

// Returns number of cycles
double readTimeOverheadInCycles() {
    Timer t;
    t.begin();
    for(int i = 0; i < N_ITERATIONS; i++);
    t.end();
    return (double) t.diff() / N_ITERATIONS;
}

// Returns time in microseconds
double readTimeOverheadInNanoSec() {
    Timer t;
    t.begin();
    for(int i = 0; i < N_ITERATIONS; i++);
    t.end();
    return t.time_diff_nano() / N_ITERATIONS;
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
    // measured in nanosec to avoid loss in precision
    s.run_func(readTimeOverheadInNanoSec); 
    cout << "Mean : " << s.mean() << " ns" << endl;
    cout << "Variance : " << s.variance() << " ns" << endl;
    cout << "Median : " << s.median() << " ns" << endl;
    cout << "Std dev : " << s.std_dev() << " ns" << endl;
}