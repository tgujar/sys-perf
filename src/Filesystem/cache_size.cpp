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

const char*  filenames[10] = {"Filesystem/temp/file512M.txt", "Filesystem/temp/file1G.txt", "Filesystem/temp/file2G.txt", "Filesystem/temp/file4G.txt", "Filesystem/temp/file42G.txt", "Filesystem/temp/file45G.txt", "Filesystem/temp/file47G.txt", "Filesystem/temp/file5G.txt", "Filesystem/temp/file6G.txt", "Filesystem/temp/file8G.txt"};
int filesizes[10] = {512, 1024, 2048, 4096, 4352, 4608, 4864, 5120, 6144, 8192};
int fileNum = 0;

using namespace std;

double rand_read_time_chrono_innerloop() {
    int blocksize = 4*1024;
    int numOfBlocksinMB = (1024*1024)/(4*1024);

    int fd = open(filenames[fileNum], O_RDONLY);
    int sizeinMB = filesizes[fileNum];
    
    if (fd < 0) 
    { 
        perror("File not read"); 
        exit(1); 
    }

    void* bf = malloc(blocksize);
    const int iter = 100;
    long array[iter];
    const int numOfBlocks = sizeinMB * numOfBlocksinMB;
    time_t t;
    srand((unsigned) time(&t));
    for(int i=0; i < iter; i++)
    {
        array[i] = rand() %numOfBlocks ;
        array[i] = array[i]*blocksize;
    }
    off_t offset;
    auto start = chrono::steady_clock::now();
    for(ssize_t i = iter; i > 0; i--) {
        offset = lseek(fd, array[i], SEEK_SET);
        read(fd, bf, blocksize);
    }
    auto end = chrono::steady_clock::now();
    free(bf);
    close(fd);
    return double(chrono::duration_cast<chrono::microseconds>(end - start).count()) / iter;
}

double rand_read_time_rtdsc_innerloop() {
    int blocksize = 4*1024;
    int numOfBlocksinMB = (1024*1024)/(4*1024);

    int fd = open(filenames[fileNum], O_RDONLY);
    int sizeinMB = filesizes[fileNum];
    
    if (fd < 0) 
    { 
        perror("File not read"); 
        exit(1); 
    }

    void* bf = malloc(blocksize);
    const int iter = 1000;
    long array[iter];
    const int numOfBlocks = sizeinMB * numOfBlocksinMB;
    time_t t1;
    srand((unsigned) time(&t1));
    for(int i=0; i < iter; i++)
    {
        array[i] = rand() %numOfBlocks ;
        array[i] = array[i]*blocksize;
    }
    off_t offset;
    Timer t;
    t.begin();
    for(ssize_t i = iter; i > 0; i--) {
        offset = lseek(fd, array[i], SEEK_SET);
        read(fd, bf, blocksize);
    }
    t.end();
    free(bf);
    close(fd);
    return t.time_diff_micro() / iter;
}

void readSeq(){
    int blocksize = 4*1024;
    int numOfBlocksinMB = (1024*1024)/(4*1024);

    int fd = open(filenames[fileNum], O_RDONLY);
    int sizeinMB = filesizes[fileNum];
    
    if (fd < 0) 
    { 
        perror("File not read"); 
        exit(1); 
    }

    void* bf = malloc(blocksize);
    const int numOfBlocks = sizeinMB * numOfBlocksinMB;
    for(ssize_t i = numOfBlocks; i > 0; i--) {
        read(fd, bf, blocksize);
    }
    free(bf);
    close(fd);
    return;
}

int main() {
    for (int i = 0; i < 10; i++) {
        fileNum = i;
        cout<<"Size of the file:"<<filesizes[i]<<endl;
        readSeq();
        Stats<double> s(50), t(50);
        use_cores(vector<int> {0});
        t.run_func(rand_read_time_rtdsc_innerloop);
        cout << "Mean (rtdsc): "<< t.mean() << " us" << endl;
        cout << "Standard deviation (rtdsc): "<< t.std_dev() << " us"<< endl;
        cout<<endl<<endl;
    }
}