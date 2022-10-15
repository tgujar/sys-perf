#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <sched.h>
#include "../utils/timer.hpp"

using namespace std;
int main() {
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(0, &set);
    if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &set) == -1) {
        exit(EXIT_FAILURE);
    }
    Timer t;
    t.begin();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    t.end();
    cout << t.diff();
}