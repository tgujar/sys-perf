// Experiment to measure overhead of reading Read Time-Stamp Counter (RTDSC)

#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <sched.h>
#include "timer.hpp"
#include "stats.hpp"
#include "proc.hpp"
using namespace std;

const int N_RUNS = 100;
const int N_ITERATIONS = 10000;

// Returns number of cycles consumed in reading RTDSC
double readTimeOverheadInCycles() {
    Timer t;
    double n_cycles = 0.0;
    for (int i = 0; i < N_ITERATIONS; i++) {
        t.begin();
        t.end();
        n_cycles += t.diff();
    }
    return n_cycles / N_ITERATIONS;
}

// Returns time consumed in reading RTDSC 
double readTimeOverheadInMicroSec() {
    Timer t;
    double time = 0.0;
    for (int i = 0; i < N_ITERATIONS; i++) {
        t.begin();
        t.end();
        time += t.time_diff_nano();
    }
    return time / N_ITERATIONS;
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
    cout << "Mean : " << s.mean() << " ns" << endl;
    cout << "Variance : " << s.variance() << " ns" << endl;
    cout << "Median : " << s.median() << " ns" << endl;
    cout << "Std dev : " << s.std_dev() << " ns" << endl;
}