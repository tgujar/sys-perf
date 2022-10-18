// Experiment to measure overhead of procedure call

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

// noinline prevents the compiler to do optimization like inlining the function
void __attribute__ ((noinline)) noParam() {}

void __attribute__ ((noinline)) oneParam(int param1) {}

void __attribute__ ((noinline)) twoParams(int param1, int param2) {}

void __attribute__ ((noinline)) threeParams(int param1, int param2, int param3) {}

void __attribute__ ((noinline)) fourParams(int param1, int param2, int param3, int param4) {}

void __attribute__ ((noinline)) fiveParams(int param1, int param2, int param3, int param4,
                 int param5) {}

void __attribute__ ((noinline)) sixParams(int param1, int param2, int param3, int param4, 
                int param5, int param6) {}

void __attribute__ ((noinline)) sevenParams(int param1, int param2, int param3, int param4, 
                  int param5, int param6, int param7) {}


double noParamsCall(bool isUnitCycle) {
    Timer t;
    double time = 0.0;
    for (int i = 0; i < N_ITERATIONS; i++) {
        t.begin();
        noParam();
        t.end();
        if (isUnitCycle) time += t.diff();
        else time += t.time_diff_micro();
    }
    return time / N_ITERATIONS;
}

double oneParamCall(bool isUnitCycle) {
    Timer t;
    double time = 0.0;
    for (int i = 0; i < N_ITERATIONS; i++) {
        t.begin();
        oneParam(10);
        t.end();
        if (isUnitCycle) time += t.diff();
        else time += t.time_diff_micro();
    }
    return time / N_ITERATIONS;
}

double twoParamsCall(bool isUnitCycle) {
    Timer t;
    double time = 0.0;
    for (int i = 0; i < N_ITERATIONS; i++) {
        t.begin();
        twoParams(10, 10);
        t.end();
        if (isUnitCycle) time += t.diff();
        else time += t.time_diff_micro();
    }
    return time / N_ITERATIONS;
}

double threeParamsCall(bool isUnitCycle) {
    Timer t;
    double time = 0.0;
    for (int i = 0; i < N_ITERATIONS; i++) {
        t.begin();
        threeParams(10, 10, 10);
        t.end();
        if (isUnitCycle) time += t.diff();
        else time += t.time_diff_micro();
    }
    return time / N_ITERATIONS;
}

double fourParamsCall(bool isUnitCycle) {
    Timer t;
    double time = 0.0;
    for (int i = 0; i < N_ITERATIONS; i++) {
        t.begin();
        fourParams(10, 10, 10, 10);
        t.end();
        if (isUnitCycle) time += t.diff();
        else time += t.time_diff_micro();
    }
    return time / N_ITERATIONS;
}

double fiveParamsCall(bool isUnitCycle) {
    Timer t;
    double time = 0.0;
    for (int i = 0; i < N_ITERATIONS; i++) {
        t.begin();
        fiveParams(10, 10, 10, 10, 10);
        t.end();
        if (isUnitCycle) time += t.diff();
        else time += t.time_diff_micro();
    }
    return time / N_ITERATIONS;
}

double sixParamsCall(bool isUnitCycle) {
    Timer t;
    double time = 0.0;
    for (int i = 0; i < N_ITERATIONS; i++) {
        t.begin();
        sixParams(10, 10, 10, 10, 10, 10);
        t.end();
        if (isUnitCycle) time += t.diff();
        else time += t.time_diff_micro();
    }
    return time / N_ITERATIONS;
}

double sevenParamsCall(bool isUnitCycle) {
    Timer t;
    double time = 0.0;
    for (int i = 0; i < N_ITERATIONS; i++) {
        t.begin();
        sevenParams(10, 10, 10, 10, 10, 10, 10);
        t.end();
        if (isUnitCycle) time += t.diff();
        else time += t.time_diff_micro();
    }
    return time / N_ITERATIONS;
}

int main() {
    Stats<double> s(N_RUNS);
    use_cores(vector<int> {0}); // force process to use only single core
    
    // No parameter function call
    s.reset_vals();
    s.run_func(noParamsCall, true);
    cout << "No Param call\n";
    cout << "Mean : " << s.mean() << " cycles" << endl;
    cout << "Variance : " << s.variance() << " cycles" << endl;
    cout << "Median : " << s.median() << " cycles" << endl;
    cout << "Std dev : " << s.std_dev() << " cycles" << endl;
    s.reset_vals();
    s.run_func(noParamsCall, false);
    cout << "Mean : " << s.mean() << " us" << endl;
    cout << "Variance : " << s.variance() << " us" << endl;
    cout << "Median : " << s.median() << " us" << endl;
    cout << "Std dev : " << s.std_dev() << " us\n" << endl;

    // One parameter function call
    s.reset_vals();
    s.run_func(oneParamCall, true);
    cout << "One Param call\n";
    cout << "Mean : " << s.mean() << " cycles" << endl;
    cout << "Variance : " << s.variance() << " cycles" << endl;
    cout << "Median : " << s.median() << " cycles" << endl;
    cout << "Std dev : " << s.std_dev() << " cycles" << endl;
    s.reset_vals();
    s.run_func(oneParamCall, false);
    cout << "Mean : " << s.mean() << " us" << endl;
    cout << "Variance : " << s.variance() << " us" << endl;
    cout << "Median : " << s.median() << " us" << endl;
    cout << "Std dev : " << s.std_dev() << " us\n" << endl;

    // Two parameters function call
    s.reset_vals();
    s.run_func(twoParamsCall, true);
    cout << "Two Params call\n";
    cout << "Mean : " << s.mean() << " cycles" << endl;
    cout << "Variance : " << s.variance() << " cycles" << endl;
    cout << "Median : " << s.median() << " cycles" << endl;
    cout << "Std dev : " << s.std_dev() << " cycles" << endl;
    s.reset_vals();
    s.run_func(twoParamsCall, false);
    cout << "Mean : " << s.mean() << " us" << endl;
    cout << "Variance : " << s.variance() << " us" << endl;
    cout << "Median : " << s.median() << " us" << endl;
    cout << "Std dev : " << s.std_dev() << " us\n" << endl;

    // Three parameters function call
    s.reset_vals();
    s.run_func(threeParamsCall, true);
    cout << "Three Params call\n";
    cout << "Mean : " << s.mean() << " cycles" << endl;
    cout << "Variance : " << s.variance() << " cycles" << endl;
    cout << "Median : " << s.median() << " cycles" << endl;
    cout << "Std dev : " << s.std_dev() << " cycles" << endl;
    s.reset_vals();
    s.run_func(threeParamsCall, false);
    cout << "Mean : " << s.mean() << " us" << endl;
    cout << "Variance : " << s.variance() << " us" << endl;
    cout << "Median : " << s.median() << " us" << endl;
    cout << "Std dev : " << s.std_dev() << " us\n" << endl;

    // Four parameters function call
    s.reset_vals();
    s.run_func(fourParamsCall, true);
    cout << "Four Params call\n";
    cout << "Mean : " << s.mean() << " cycles" << endl;
    cout << "Variance : " << s.variance() << " cycles" << endl;
    cout << "Median : " << s.median() << " cycles" << endl;
    cout << "Std dev : " << s.std_dev() << " cycles" << endl;
    s.reset_vals();
    s.run_func(fourParamsCall, false);
    cout << "Mean : " << s.mean() << " us" << endl;
    cout << "Variance : " << s.variance() << " us" << endl;
    cout << "Median : " << s.median() << " us" << endl;
    cout << "Std dev : " << s.std_dev() << " us\n" << endl;

    // Five parameter function call
    s.reset_vals();
    s.run_func(fiveParamsCall, true);
    cout << "Five Params call\n";
    cout << "Mean : " << s.mean() << " cycles" << endl;
    cout << "Variance : " << s.variance() << " cycles" << endl;
    cout << "Median : " << s.median() << " cycles" << endl;
    cout << "Std dev : " << s.std_dev() << " cycles" << endl;
    s.reset_vals();
    s.run_func(fiveParamsCall, false);
    cout << "Mean : " << s.mean() << " us" << endl;
    cout << "Variance : " << s.variance() << " us" << endl;
    cout << "Median : " << s.median() << " us" << endl;
    cout << "Std dev : " << s.std_dev() << " us\n" << endl;

    // Six parameter function call
    s.reset_vals();
    s.run_func(sixParamsCall, true);
    cout << "Six Params call\n";
    cout << "Mean : " << s.mean() << " cycles" << endl;
    cout << "Variance : " << s.variance() << " cycles" << endl;
    cout << "Median : " << s.median() << " cycles" << endl;
    cout << "Std dev : " << s.std_dev() << " cycles" << endl;
    s.reset_vals();
    s.run_func(sixParamsCall, false);
    cout << "Mean : " << s.mean() << " us" << endl;
    cout << "Variance : " << s.variance() << " us" << endl;
    cout << "Median : " << s.median() << " us" << endl;
    cout << "Std dev : " << s.std_dev() << " us\n" << endl;

    // Seven parameter function call
    s.reset_vals();
    s.run_func(sevenParamsCall, true);
    cout << "Seven Params call\n";
    cout << "Mean : " << s.mean() << " cycles" << endl;
    cout << "Variance : " << s.variance() << " cycles" << endl;
    cout << "Median : " << s.median() << " cycles" << endl;
    cout << "Std dev : " << s.std_dev() << " cycles" << endl;
    s.reset_vals();
    s.run_func(sevenParamsCall, false);
    cout << "Mean : " << s.mean() << " us" << endl;
    cout << "Variance : " << s.variance() << " us" << endl;
    cout << "Median : " << s.median() << " us" << endl;
    cout << "Std dev : " << s.std_dev() << " us\n" << endl;
}