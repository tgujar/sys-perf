#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <sched.h>
#include "timer.hpp"
#include "stats.hpp"
#include "proc.hpp"


using namespace std;
double cpu_freq() {
    Timer t;
    t.begin();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    t.end();
    return t.time_diff_micro();
}

int main() {
    Stats<double> s(10);
    use_cores(vector<int> {0});
    s.run_func(cpu_freq);
    cout << s.mean() << endl << s.std_dev() << endl << s.variance() << endl << s.median();
}