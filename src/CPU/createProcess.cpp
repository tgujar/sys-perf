#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <sys/wait.h>
#include <sched.h>
#include <stdexcept>
#include "timer.hpp"
#include "stats.hpp"
#include "proc.hpp"


using namespace std;

// getpid() cache has been deprecated, see https://man7.org/linux/man-pages/man2/getpid.2.html

double create_process_time_chrono_innerloop() {
    auto start = chrono::steady_clock::now();
    const int iter = 1000;
    for(ssize_t i = iter; i > 0; i--) {
        pid_t chid = fork();
        if (chid == -1) {
            continue;
        } else if (chid == 0) {//child
            exit(1);
        }
    }
    auto end = chrono::steady_clock::now();
    return double(chrono::duration_cast<chrono::microseconds>(end - start).count()) / iter;
}

double create_process_time_chrono_outerloop() {
    double total = 0;
    
    const int iter = 1000;
    for(ssize_t i = iter; i > 0; i--) {
        auto start = chrono::steady_clock::now();
        pid_t chid = fork();
        if (chid == -1) {
            continue;
        } else if (chid == 0) {//child
            exit(1);
        }
        else{
            auto end = chrono::steady_clock::now();
            total+=double(chrono::duration_cast<chrono::microseconds>(end - start).count());
        }
        
    }
    
    return total / iter;
}

double create_process_time_rtdsc_innerloop() {
    Timer t;
    t.begin();
    const int iter = 1000;
    for(ssize_t i = iter; i > 0; i--) {
        pid_t chid = fork();
        if (chid == -1) {
            continue;
        } else if (chid == 0) {//child
            exit(1);
        }
    }
    t.end();
    return t.time_diff_micro() / iter;
}

double create_process_time_rtdsc_outerloop() {
    const int iter = 1000;
    double total = 0;
    for(ssize_t i = iter; i > 0; i--) {
        Timer t;
        t.begin();
        pid_t chid = fork();
        if (chid == -1) {
            continue;
        } else if (chid == 0) {//child
            exit(1);
        }
        else{
            t.end();
            total+=t.time_diff_micro();
        }
    }
    
    return total / iter;
}


int main() {
    Stats<double> s(100), t(100);
    use_cores(vector<int> {0});
    s.run_func(create_process_time_chrono_innerloop);
    cout << "Mean (chrono): "<< s.mean() << " us"<< endl;
    cout << "Standard deviation (chrono): "<< s.std_dev() << " us"<< endl;
    t.run_func(create_process_time_rtdsc_innerloop);
    cout << "Mean (rtdsc): "<< t.mean() << " us" << endl;
    cout << "Standard deviation (rtdsc): "<< t.std_dev() << " us"<< endl;
}