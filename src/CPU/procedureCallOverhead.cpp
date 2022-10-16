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
const int N_ITERATIONS = 1000;

void noParam() {}

void oneParam(int param1) {}

void twoParams(int param1, int param2) {}

void threeParams(int param1, int param2, int param3) {}

void fourParams(int param1, int param2, int param3, int param4) {}

void fiveParams(int param1, int param2, int param3, int param4,
                 int param5) {}

void sixParams(int param1, int param2, int param3, int param4, 
                int param5, int param6) {}

void sevenParams(int param1, int param2, int param3, int param4, 
                  int param5, int param6, int param7) {}


double noParamsCall() {
    Timer t;
    double time = 0.0;
    for (int i = 0; i < N_ITERATIONS; i++) {
        t.begin();
        noParam();
        t.end();
        time += t.time_diff_micro();
    }
    return time / N_ITERATIONS;
}

double oneParamCall() {
    Timer t;
    double time = 0.0;
    for (int i = 0; i < N_ITERATIONS; i++) {
        t.begin();
        oneParam(10);
        t.end();
        time += t.time_diff_micro();
    }
    return time / N_ITERATIONS;
}

double twoParamsCall() {
    Timer t;
    double time = 0.0;
    for (int i = 0; i < N_ITERATIONS; i++) {
        t.begin();
        twoParams(10, 10);
        t.end();
        time += t.time_diff_micro();
    }
    return time / N_ITERATIONS;
}

double threeParamsCall() {
    Timer t;
    double time = 0.0;
    for (int i = 0; i < N_ITERATIONS; i++) {
        t.begin();
        threeParams(10, 10, 10);
        t.end();
        time += t.time_diff_micro();
    }
    return time / N_ITERATIONS;
}

double fourParamsCall() {
    Timer t;
    double time = 0.0;
    for (int i = 0; i < N_ITERATIONS; i++) {
        t.begin();
        fourParams(10, 10, 10, 10);
        t.end();
        time += t.time_diff_micro();
    }
    return time / N_ITERATIONS;
}

double fiveParamsCall() {
    Timer t;
    double time = 0.0;
    for (int i = 0; i < N_ITERATIONS; i++) {
        t.begin();
        fiveParams(10, 10, 10, 10, 10);
        t.end();
        time += t.time_diff_micro();
    }
    return time / N_ITERATIONS;
}

double sixParamsCall() {
    Timer t;
    double time = 0.0;
    for (int i = 0; i < N_ITERATIONS; i++) {
        t.begin();
        sixParams(10, 10, 10, 10, 10, 10);
        t.end();
        time += t.time_diff_micro();
    }
    return time / N_ITERATIONS;
}

double sevenParamsCall() {
    Timer t;
    double time = 0.0;
    for (int i = 0; i < N_ITERATIONS; i++) {
        t.begin();
        sevenParams(10, 10, 10, 10, 10, 10, 10);
        t.end();
        time += t.time_diff_micro();
    }
    t.end();
    return time / N_ITERATIONS;
}

int main() {
    Stats<double> s(N_RUNS);
    use_cores(vector<int> {0}); // force process to use only single core
    
    // No parameter function call
    s.reset_vals();
    s.run_func(noParamsCall);
    cout << "No Param call\n";
    cout << "Mean : " << s.mean() << " us" << endl;

    // One parameter function call
    s.reset_vals();
    s.run_func(oneParamCall);
    cout << "One Param call\n";
    cout << "Mean : " << s.mean() << " us" << endl;

    // Two parameters function call
    s.reset_vals();
    s.run_func(twoParamsCall);
    cout << "Two Params call\n";
    cout << "Mean : " << s.mean() << " us" << endl;

    // Three parameters function call
    s.reset_vals();
    s.run_func(threeParamsCall);
    cout << "Three Params call\n";
    cout << "Mean : " << s.mean() << " us" << endl;

    // Four parameters function call
    s.reset_vals();
    s.run_func(fourParamsCall);
    cout << "Four Params call\n";
    cout << "Mean : " << s.mean() << " us" << endl;

    // Five parameter function call
    s.reset_vals();
    s.run_func(fiveParamsCall);
    cout << "Five Params call\n";
    cout << "Mean : " << s.mean() << " us" << endl;

    // Six parameter function call
    s.reset_vals();
    s.run_func(sixParamsCall);
    cout << "Six Params call\n";
    cout << "Mean : " << s.mean() << " us" << endl;

    // Seven parameter function call
    s.reset_vals();
    s.run_func(sevenParamsCall);
    cout << "Seven Params call\n";
    cout << "Mean : " << s.mean() << " us" << endl;
}