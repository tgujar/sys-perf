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
#include "csvfile.h"

int pipes; // number of pipes or processes in ring
int footprint_arr_len; // cache footprint
const int iters = 1000;
const int max_footprint = 589824/4;

using namespace std;

void *overhead_routine(void *ptr) {
    // create pipes
    use_cores(vector<int> {1});
    int (*p)[2] = (int (*)[2]) ptr;
    char buf = 'm';
    int arr[max_footprint];
    int temp = 0;

    for (size_t i = iters; i > 0; i--) {
        for (int i = 0; i < pipes; i++) {
            read(p[i][0], &buf, 1); // read from pipe
            for (int offset = 0; offset < footprint_arr_len; offset++){
                *(arr + offset) = 1;
            }
            write(p[(i + 1) % pipes][1], &buf, 1); // write to pipe
        }
    }
    return NULL;
}

double overhead() {
    
    int p[pipes][2];
    pthread_t tid;
    char buf = 'm';

    for (int i = 0; i < pipes; i++) {
        if (pipe(p[i]) == -1) {
            throw std::runtime_error("cant create pipe");
        }
    }
    pthread_create(&tid, NULL, overhead_routine, (void *) p);

    Timer t;
    t.begin();
    write(p[0][1], &buf, 1); // write to pipe
    pthread_join(tid, NULL);
    t.end();

    for (int i = 0; i < pipes; i++) {
        close(p[i][0]);
        close(p[i][1]);
    }

    return t.time_diff_micro() / (iters * pipes); // return pipe overhead
}

void *kern_thread_ring_routine(void *ptr) {
    // create pipes
    use_cores(vector<int> {1});
    int *p = (int *) ptr;
    char buf = 'm';
    int arr[max_footprint];
    int temp = 0;

    for (size_t i = iters; i > 0; i--) {
        read(p[0], &buf, 1); // read from pipe
        for (int offset = 0; offset < footprint_arr_len; offset++){
            *(arr + offset) = 1;
        }
        write(p[1], &buf, 1); // write to pipe
    }
    delete p; // avoid mem leak :)
    return NULL;
}

double kern_thread_ring() {
    int p[pipes][2];
    pthread_t tid[pipes];
    for (int i = 0; i < pipes; i++) {
        if (pipe(p[i]) == -1) {
            throw std::runtime_error("cant create pipe");
        }
    }

    char buf = 'm';

    for (int i  = 0; i < pipes; i++) {
        // cant be allocated on stack, when the next iteration is run these values will get overwritten
        // this will lead to all the kernel threads having the same file descriptors
        int *ktp = new int[2] {p[i][0], p[(i+1) % pipes][1]}; 
        pthread_create(&tid[i], NULL, kern_thread_ring_routine, (void *) ktp);
    }
    
    Timer t;
    t.begin();
    write(p[0][1], &buf, 1); // write to pipe
    for(int i = 0; i < pipes; i++) {
        pthread_join(tid[i], NULL); 
    }
    t.end();

    for (int i = 0; i < pipes; i++) {
        close(p[i][0]);
        close(p[i][1]);
    }

    return t.time_diff_micro()  / (iters * pipes); // return total time
}

int main() {
    vector<int> pipe_size {2, 4, 8, 16, 32};
    vector<int> footprint_size {0, 2048/4, 4096/4, 8192/4, 16384/4, 32768/4, 65536/4, 131072/4, 589824/4}; // {0B, 2KB, 4KB, 8KB, 16KB, 32KB, 64KB, 128KB}
    csvfile out("../data/ctxswitchkernel.csv");
    out << "No. of pipes" << "Footprint size(KB)" << "Mean overhead (us)" << "Mean total (us)" << "Mean ctx switch (us)" << "Std dev (us)" << endrow; 
    use_cores(vector<int> {0});

    for (auto &tp: pipe_size) {
        pipes = tp;
        for(auto &tf: footprint_size) {
            footprint_arr_len = tf;
            Stats<double> s(10), t(10);
            s.run_func(overhead);
            t.run_func(kern_thread_ring);
            out << pipes << (footprint_arr_len * 4) / 1024 << s.mean() << t.mean() << t.mean() - s.mean() << t.std_dev() << endrow;
        }
    }
}