#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <sys/wait.h>
#include <sched.h>
#include <pthread.h>
#include <stdexcept>
#include "timer.hpp"
#include "stats.hpp"
#include "proc.hpp"


using namespace std;

// getpid() cache has been deprecated, see https://man7.org/linux/man-pages/man2/getpid.2.html
void *routine(void *ptr) {
    // create pipes
    pthread_exit(NULL);
}
double create_thread_time_chrono_innerloop() {
    int p;
    pthread_t tid;
    const int iter = 10000;
    auto start = chrono::steady_clock::now();
    for(ssize_t i = iter; i > 0; i--) {
        pthread_create(&tid, NULL, routine, (void *) p);
    }
    auto end = chrono::steady_clock::now();
    return double(chrono::duration_cast<chrono::microseconds>(end - start).count()) / iter;
}

double create_thread_time_chrono_outerloop() {
    double total = 0;
    const int iter = 10000;
    int p;
    pthread_t tid;
    for(ssize_t i = iter; i > 0; i--) {
        auto start = chrono::steady_clock::now();
        pthread_create(&tid, NULL, routine, (void *) p);
        auto end = chrono::steady_clock::now();
        total+=double(chrono::duration_cast<chrono::microseconds>(end - start).count());
    }
    
    return total / iter;
}

double create_thread_time_rtdsc_innerloop() {
    Timer t;
    int p;
    pthread_t tid;
    t.begin();
    const int iter = 10000;
    for(ssize_t i = iter; i > 0; i--) {
        pthread_create(&tid, NULL, routine, (void *) p);
    }
    t.end();
    return t.time_diff_micro() / iter;
}

double create_thread_time_rtdsc_outerloop() {
    const int iter = 10000;
    double total = 0;
    for(ssize_t i = iter; i > 0; i--) {
        int p;
        pthread_t tid;
        Timer t;
        t.begin();
        pthread_create(&tid, NULL, routine, (void *) p);
        t.end();
        total+=t.time_diff_micro();
    }
    
    return total / iter;
}


int main() {
    Stats<double> s(10), t(10);
    use_cores(vector<int> {0});
    s.run_func(create_thread_time_chrono_innerloop);
    cout << "Mean (chrono): "<< s.mean() << " us"<< endl;
    cout << "Standard deviation (chrono): "<< s.std_dev() << " us"<< endl;
    t.run_func(create_thread_time_rtdsc_innerloop);
    cout << "Mean (rtdsc): "<< t.mean() << " us" << endl;
    cout << "Standard deviation (rtdsc): "<< t.std_dev() << " us"<< endl;
}