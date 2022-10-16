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

const int pipes = 10; // number of pipes or processes in ring
const int footprint_vector_len = 1000000; // cache footprint

using namespace std;
double overhead() {
    const int iters = 100;
    int p[pipes][2];
    char buf = 'm';

    // create pipes
    for (int i = 0; i < pipes; i++) {
        if (pipe(p[i]) == -1) {
            throw std::runtime_error("cant create pipe");
        }
    }

    auto start = chrono::steady_clock::now();
    for (size_t i = iters; i > 0; i--) {
        for (int i = 0; i < pipes; i++) {
            write(p[i][1], &buf, 1); // write to pipe
            read(p[i][0], &buf, 1); // read from pipe
        }
    }
    auto end = chrono::steady_clock::now();
    for (int i = 0; i < pipes; i++) {
        close(p[i][0]);
    }
    return double(chrono::duration_cast<chrono::microseconds>(end - start).count()) / (iters * pipes); // return pipe overhead
}

double total_pass() {
    const int iters = 100;
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
            vector<int> f(footprint_vector_len, 1);
            for (int j = 0; j < iters; j++) {
                read(p[(i - 1 + pipes) % pipes][0], &buf, 1); // first iteration waits for parent to signal
                write(p[i % pipes][1], &buf, 1);
            }
            exit(0);
        }
    }
    
    auto start = chrono::steady_clock::now();
    write(p[0][1], &buf, 1); // start chain from parent
    while(wait(NULL) > 0); // wait for chain to finish
    auto end = chrono::steady_clock::now();

    return double(chrono::duration_cast<chrono::microseconds>(end - start).count()) / (iters * pipes); // return total time
}

int main() {
    Stats<double> s(10), t(10);
    use_cores(vector<int> {0});
    s.run_func(overhead);
    t.run_func(total_pass);
    cout << "Mean overhead: " << s.mean() << " us" << endl;
    cout << "Mean total: " << t.mean() << " us" << endl;
    cout << "Mean ctx switch: " << t.mean() - s.mean() << endl;
}