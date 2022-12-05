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
#define UNROLL 16

double read_BW() {
    Timer t;
    int *ptr;
    
    int result = 0; 
    posix_memalign((void**) &ptr, ALIGNMENT, ARR_SIZE*sizeof(int));
    for(int i = 0; i < ARR_SIZE; i++) {
        ptr[i] = i;
    }

    t.begin();
    // int sign = -1; //https://gcc.gnu.org/projects/tree-ssa/vectorization.html Idiom recognition causes misleading values
    // either use sign to break idiom recognition or disable ftree-vectorization
    // for(int i = 0; i < ARR_SIZE; i+=16) {
    //     #pragma unroll // unrolled loop to avoid skewed measurements from jmp
    //     for (int j = 0; j < 16; j++) {
    //         result += ptr[i+j] * sign;
    //         sign *= -1;
    //     }
    // }

    for(int i = 0; i < ARR_SIZE; i+=UNROLL) {
        #pragma unroll // unrolled loop to avoid skewed measurements from jmp
        for (int j = 0; j < UNROLL; j++) {
            result += ptr[i+j];
        }
    }

    t.end();
    free(ptr);

    volatile int temp =  result; // forced volatile int to prevent compiler optimizing away dead code
    return ARR_SIZE*sizeof(int) / (t.time_diff_micro() * 1000); // return total time
}

int main() {
    use_cores({1});
    nice(-20);
    Stats<double> r(ITERATIONS);
    r.run_func(read_BW);
    cout << endl << "Read BW" << endl <<"Mean: "<< r.mean() <<" GB/s" << endl << "Std dev: " << r.std_dev() << endl;
}
