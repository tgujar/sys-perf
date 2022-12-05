#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <sys/wait.h>
#include <sched.h>
#include <stdexcept>
#include <malloc.h>
#include <cmath>
#include "timer.hpp"
#include "stats.hpp"
#include "proc.hpp"
#include "csvfile.h"

using namespace std;

#define ARR_SIZE pow(2, 16)
#define ALIGNMENT 64
#define ITERATIONS 100

double write_BW() {
    Timer t;
    int *ptr;
    posix_memalign((void**) &ptr, ALIGNMENT, ARR_SIZE*sizeof(int));

    t.begin();
    for(int i = 0; i < ARR_SIZE; i+=16) {
        #pragma unroll // unrolled loop to avoid skewed measurements from jmp
        for (int j = 0; j < 16; j++) {
            ptr[i+j] = i+j;
        }
    }
    t.end();
    free(ptr);
    return ARR_SIZE*sizeof(int) / (t.time_diff_micro() * 1000); // return total time
}

int main() {
    use_cores({1});
    nice(-20);
    Stats<double> w(ITERATIONS);
    w.run_func(write_BW);
    cout << endl << "Write BW" << endl <<"Mean: "<< w.mean() <<" GB/s" << endl << "Std dev: " << w.std_dev() << endl;
}