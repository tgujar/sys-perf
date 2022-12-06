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

const char*  filenames[8] = {"Filesystem/temp/file64M.txt", "Filesystem/temp/file128M.txt", "Filesystem/temp/file256M.txt", "Filesystem/temp/file512M.txt", "Filesystem/temp/file1G.txt", "Filesystem/temp/file2G.txt", "Filesystem/temp/file4G.txt", "Filesystem/temp/file8G.txt"};
int filesizes[8] = {64, 128, 256, 512, 1024, 2048, 4096, 8192};
int fileNum = 0;

using namespace std;

double seq_read_time_chrono_innerloop() {
    int blocksize = 4*1024;
    int numOfBlocksinMB = (1024*1024)/(4*1024);

    int ft;
    char* data = "3";

    sync();
    ft = open("/proc/sys/vm/drop_caches", O_WRONLY);
    write(ft, data, sizeof(char));
    close(ft);

    int fd = open(filenames[fileNum], O_RDONLY | O_DIRECT);
    int sizeinMB = filesizes[fileNum];
    
    if (fd < 0) 
    { 
        perror("File not read"); 
        exit(1); 
    }

    void* bf = malloc(blocksize);
    const int iter = 10000;
    const int numOfBlocks = sizeinMB * numOfBlocksinMB - iter - 1;
    time_t t;
    srand((unsigned) time(&t));
    long offset = rand() % numOfBlocks;
    offset = offset*blocksize;
    lseek(fd, offset, SEEK_SET);
    auto start = chrono::steady_clock::now();
    for(ssize_t i = iter; i > 0; i--) {
        read(fd, bf, blocksize);
    }
    auto end = chrono::steady_clock::now();
    free(bf);
    close(fd);
    return double(chrono::duration_cast<chrono::microseconds>(end - start).count()) / iter;
}

double seq_read_time_rtdsc_innerloop() {
    int blocksize = 4*1024;
    int numOfBlocksinMB = (1024*1024)/(4*1024);

    int fd = open(filenames[fileNum], O_RDONLY | O_DIRECT);
    int sizeinMB = filesizes[fileNum];
    
    if (fd < 0) 
    { 
        perror("File not read"); 
        exit(1); 
    }

    void* bf = malloc(blocksize);
    const int iter = 10000;
    const int numOfBlocks = sizeinMB * numOfBlocksinMB - iter - 1;
    time_t t1;
    srand((unsigned) time(&t1));
    long offset = rand() % numOfBlocks;
    offset = offset*blocksize;
    lseek(fd, offset, SEEK_SET);
    Timer t;
    t.begin();
    for(ssize_t i = iter; i > 0; i--) {
        read(fd, bf, blocksize);
    }
    t.end();
    free(bf);
    close(fd);
    return t.time_diff_micro() / iter;
}

int main() {
    for (int i = 0; i < 7; i++) {
        fileNum = i;
        cout<<"Size of the file:"<<filesizes[i]<<endl;
        Stats<double> s(100), t(100);
        use_cores(vector<int> {0});
        s.run_func(seq_read_time_chrono_innerloop);
        cout << "Mean (chrono): "<< s.mean() << " us"<< endl;
        cout << "Standard deviation (chrono): "<< s.std_dev() << " us"<< endl;
        t.run_func(seq_read_time_rtdsc_innerloop);
        cout << "Mean (rtdsc): "<< t.mean() << " us" << endl;
        cout << "Standard deviation (rtdsc): "<< t.std_dev() << " us"<< endl;
        cout<<endl<<endl;
    }
}