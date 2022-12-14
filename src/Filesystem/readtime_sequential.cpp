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

const char*  filenames[12] = {"Filesystem/temp/file4M.txt", "Filesystem/temp/file8M.txt", "Filesystem/temp/file16M.txt", "Filesystem/temp/file32M.txt", "Filesystem/temp/file64M.txt", "Filesystem/temp/file128M.txt", "Filesystem/temp/file256M.txt", "Filesystem/temp/file512M.txt", "Filesystem/temp/file1G.txt", "Filesystem/temp/file2G.txt", "Filesystem/temp/file4G.txt", "Filesystem/temp/file8G.txt"};
int filesizes[12] = {4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192};
int fileNum = 0;

using namespace std;

double seq_read_time_rtdsc_innerloop() {
    int blocksize = 4*1024;
    int numOfBlocksinMB = (1024*1024)/(4*1024);

    int ft;
    char* data = "3";

    sync();
    ft = open("/proc/sys/vm/drop_caches", O_WRONLY);
    if (write(ft, data, sizeof(char)) == -1) {
        cout << "Error in writing to drop_caches" << endl;
        exit(1);
    }
    close(ft);

    int fd = open(filenames[fileNum], O_RDONLY);
    int sizeinMB = filesizes[fileNum];
    
    if (fd < 0) 
    { 
        perror("File not read"); 
        exit(1); 
    }

    void* bf = malloc(blocksize);
    const int iter = 1000;
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
    for (int i = 0; i < 11; i++) {
        fileNum = i;
        cout<<"Size of the file:"<<filesizes[i]<<endl;
        Stats<double> s(50), t(50);
        use_cores(vector<int> {0});
        t.run_func(seq_read_time_rtdsc_innerloop);
        cout << "Mean (rtdsc): "<< t.mean() << " us" << endl;
        cout << "Standard deviation (rtdsc): "<< t.std_dev() << " us"<< endl;
        cout<<endl<<endl;
    }
}