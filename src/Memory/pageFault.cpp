#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sched.h>
#include<stdio.h> 
#include <fcntl.h> 
#include <stdexcept>
#include "timer.hpp"
#include "stats.hpp"
#include "proc.hpp"


using namespace std;

// getpid() cache has been deprecated, see https://man7.org/linux/man-pages/man2/getpid.2.html

double page_fault_time_chrono_innerloop() {
    int ft;
    char* data = "3";

    sync();
    ft = open("/proc/sys/vm/drop_caches", O_WRONLY);
    write(ft, data, sizeof(char));
    close(ft);

    long int size = 4606352424;
    int offset = 16777216;
    size -= 20*offset;
    int fd = open("sample.txt", O_RDWR);
    
    if (fd < 0) 
    { 
        perror("File not read"); 
        exit(1); 
    }
    
    char *ptr = (char*)mmap( NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0 );
    if(ptr == MAP_FAILED){
        printf("Mapping Failed\n");
        exit(1);
    }
    
    char s;

    auto start = chrono::steady_clock::now();
    const int iter = 10000;
    for(ssize_t i = iter; i > 0; i--) {
        s =  ptr[(i * offset) % (size - 1)];
    }
    auto end = chrono::steady_clock::now();
    int err = munmap(ptr, size);
    if(err != 0){
        printf("UnMapping Failed\n");
        exit(1);
    }
    return double(chrono::duration_cast<chrono::microseconds>(end - start).count()) / iter;
}

double page_fault_time_rtdsc_innerloop() {
    int ft;
    char* data = "3";

    sync();
    ft = open("/proc/sys/vm/drop_caches", O_WRONLY);
    write(ft, data, sizeof(char));
    close(ft);
    
    long int size = 4606352424;
    int offset = 16777216;
    size -= 20*offset;
    int fd = open("sample.txt", O_RDWR);
    
    if (fd < 0) 
    { 
        perror("File not read"); 
        exit(1); 
    }
    
    char *ptr = (char*)mmap( NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0 );
    if(ptr == MAP_FAILED){
        printf("Mapping Failed\n");
        exit(1);
    }
    
    char s;

    Timer t;
    t.begin();
    const int iter = 10000;
    for(ssize_t i = iter; i > 0; i--) {
        s =  ptr[(i * offset) % (size - 1)];
    }
    t.end();
    int err = munmap(ptr, size);
    if(err != 0){
        printf("UnMapping Failed\n");
        exit(1);
    }
    
    return t.time_diff_micro() / iter;
}


int main() {
    Stats<double> s(100), t(100);
    use_cores(vector<int> {0});
    s.run_func(page_fault_time_chrono_innerloop);
    cout << "Mean (chrono): "<< s.mean() << " us"<< endl;
    cout << "Standard deviation (chrono): "<< s.std_dev() << " us"<< endl;
    t.run_func(page_fault_time_rtdsc_innerloop);
    cout << "Mean (rtdsc): "<< t.mean() << " us" << endl;
    cout << "Standard deviation (rtdsc): "<< t.std_dev() << " us"<< endl;
}