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

const int pipes = 20; // number of pipes or processes in ring
const int footprint_vector_len = 100000; // cache footprint
const int iters = 100;

using namespace std;

void *overhead_routine(void *ptr) {
    // create pipes
    use_cores(vector<int> {1});
    int (*p)[2] = (int (*)[2]) ptr;
    char buf = 'm';
    for (size_t i = iters; i > 0; i--) {
        for (int i = 0; i < pipes; i++) {
            read(p[i][0], &buf, 1); // read from pipe
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
    int f[footprint_vector_len] = {1};
    char buf = 'm';
    for (size_t i = iters; i > 0; i--) {
        read(p[0], &buf, 1); // read from pipe
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
    Stats<double> s(10), t(10);
    use_cores(vector<int> {0});
    s.run_func(overhead);
    t.run_func(kern_thread_ring);
    cout << "Mean overhead: " << s.mean() << " us" << endl;
    cout << "Mean total: " << t.mean() << " us" << endl;
    cout << "Mean ctx switch: " << t.mean() - s.mean() << " us" << endl;
}