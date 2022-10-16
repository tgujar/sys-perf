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

const int N_RUNS = 10;
const int N_ITERATIONS = 1000;

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
double readTimeOverheadInSeconds() {
    Timer t;
    double time = 0.0;
    for (int i = 0; i < N_ITERATIONS; i++) {
        t.begin();
        t.end();
        time += t.time_diff_micro();
    }
    return time / N_ITERATIONS;
}


int main() {
    Stats<double> s(N_RUNS);
    use_cores(vector<int> {0}); // force process to use only single core

    s.run_func(readTimeOverheadInCycles);
    cout << "Mean : " << s.mean() << " cycles" << endl;
    
    s.reset_vals();
    s.run_func(readTimeOverheadInSeconds);
    cout << "Mean : " << s.mean() << " us" << endl;
}