#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <sched.h>
#include "timer.hpp"
#include "stats.hpp"
#include "proc.hpp"


using namespace std;

// getpid() cache has been deprecated, see https://man7.org/linux/man-pages/man2/getpid.2.html

double sys_call_time_chrono() {
    auto start = chrono::steady_clock::now();
    for(ssize_t i = 100000; i > 0; i--) {
        getpid();
    }
    auto end = chrono::steady_clock::now();
    return double(chrono::duration_cast<chrono::microseconds>(end - start).count()) / 100000;
}

double sys_call_time_rtdsc() {
    Timer t;
    t.begin();
    for(ssize_t i = 100000; i > 0; i--) {
        getpid();
    }
    t.end();
    return t.time_diff_micro() / 100000;
}



int main() {
    Stats<double> s(10), t(10);
    use_cores(vector<int> {0});
    s.run_func(sys_call_time_chrono);
    cout << "Mean (chrono): "<< s.mean() << " us"<< endl;
    t.run_func(sys_call_time_chrono);
    cout << "Mean (rtdsc): "<< t.mean() << " us" << endl;
}