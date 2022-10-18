#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <sched.h>
#include "timer.hpp"
#include "stats.hpp"
#include "proc.hpp"


using namespace std;
const int iter = 100000;
// getpid() cache has been deprecated, see https://man7.org/linux/man-pages/man2/getpid.2.html

double sys_call_time_chrono() {
    auto start = chrono::steady_clock::now();
    for(ssize_t i = iter; i > 0; i--) {
        getpid();
    }
    auto end = chrono::steady_clock::now();
    return double(chrono::duration_cast<chrono::nanoseconds>(end - start).count()) / iter;
}

double sys_call_time_rtdsc() {
    Timer t;
    t.begin();
    for(ssize_t i = iter; i > 0; i--) {
        getpid();
    }
    t.end();
    return t.time_diff_nano() / iter;
}



int main() {
    Stats<double> s(100), t(100);
    use_cores(vector<int> {0});
    s.run_func(sys_call_time_chrono);
    cout << "Mean (chrono): "<< s.mean() << " ns"<< endl;
    cout << "Std dev (chrono): "<< s.std_dev() << " ns" << endl;
    t.run_func(sys_call_time_rtdsc);
    cout << "Mean (rtdsc): "<< t.mean() << " ns" << endl;
    cout << "Std dev (rtdsc): "<< t.std_dev() << " ns" << endl;
}