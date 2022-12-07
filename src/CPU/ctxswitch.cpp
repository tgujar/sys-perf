#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <sys/wait.h>
#include <sched.h>
#include <stdexcept>
#include <malloc.h>
#include "timer.hpp"
#include "stats.hpp"
#include "proc.hpp"
#include "csvfile.h"

int pipes; // number of pipes or processes in ring
int footprint_arr_len; // cache footprint
const int iters = 100;
const int max_footprint = 589824/4;

using namespace std;
double overhead() {
    int p[pipes][2];
    char buf = 'm';

    // create pipes
    for (int i = 0; i < pipes; i++) {
        if (pipe(p[i]) == -1) {
            throw std::runtime_error("cant create pipe");
        }
    }
    
    Timer t;
    t.begin();
    //int *arr = (int*) memalign(4096, footprint_arr_len*4);
    int arr[max_footprint];
    int temp = 0;
    for (size_t i = iters; i > 0; i--) {
        for (int i = 0; i < pipes; i++) {
            write(p[i][1], &buf, 1); // write to pipe
            for (int offset = 0; offset < footprint_arr_len; offset++){
                *(arr + offset) = 1;
            }
            read(p[i][0], &buf, 1); // read from pipe
        }
    }
    t.end();
    for (int i = 0; i < pipes; i++) {
         close(p[i][0]);
         close(p[i][1]);
    }
    return t.time_diff_micro()  / (iters * pipes); // return pipe overhead
}

double total_pass() {

    int p[pipes][2];
    
    for (int i = 0; i < pipes; i++) {
        if (pipe(p[i]) == -1) {
            throw std::runtime_error("cant create pipe");
        }
    }

    char buf = 'm';
    for (int i  = 0; i < pipes; i++) {
        pid_t chid = fork();
        if (chid == -1) {
            exit(1);
        } else if (chid == 0) {
            char buf;
            use_cores(vector<int> {1});
            //int *arr = (int*) memalign(4096, footprint_arr_len*4);
            int arr[max_footprint];
            int temp = 0;
            for (int j = 0; j < iters; j++) {
                read(p[(i - 1 + pipes) % pipes][0], &buf, 1); // first iteration waits for parent to signal
                for (int offset = 0; offset < footprint_arr_len; offset++){
                    *(arr + offset) = 1;
                }
                write(p[i % pipes][1], &buf, 1);
            }
            exit(0);
        }
    }
    
    Timer t;
    t.begin();
    write(p[0][1], &buf, 1); // start chain from parent
    while(wait(NULL) > 0); // wait for chain to finish
    t.end();
    for (int i = 0; i < pipes; i++) {
         close(p[i][0]);
         close(p[i][1]);
    }
    return t.time_diff_micro() / (iters * pipes); // return total time
}

int main() {
    vector<int> pipe_size {2, 4, 8, 16, 32};
    vector<int> footprint_size {0, 2048/4, 4096/4, 8192/4, 16384/4, 32768/4, 65536/4, 131072/4, 589824/4}; // {0B, 2KB, 4KB, 8KB, 16KB, 32KB, 64KB, 128KB}
    csvfile out("../data/CPU/ctxswitch.csv");
    out << "No. of pipes" << "Footprint size(KB)" << "Mean overhead (us)" << "Mean total (us)" << "Mean ctx switch (us)" << "Std dev (us)" << endrow; 
    use_cores(vector<int> {0});

    for (auto &tp: pipe_size) {
        pipes = tp;
        for(auto &tf: footprint_size) {
            footprint_arr_len = tf;
            Stats<double> s(10), t(10);
            s.run_func(overhead);
            t.run_func(total_pass);
            out << pipes << (footprint_arr_len * 4) / 1024 << s.mean() << t.mean() << t.mean() - s.mean() << t.std_dev() << endrow;
        }
    }
}