#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "stats.hpp"
#include "proc.hpp"
#include "timer.hpp"
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
using namespace std;

const int N_RUNS = 5;
const int N_ITERATIONS = 5;
const string FILE_PREFIX = "file";
const string FILE_SUFFIX = ".txt";
const string FILE_DIRECTORY = "../temp_files/";
int n_processes;

// Returns block size
int get_fs_block_size()
{
    // cout<<"block size enter"<<endl;
    // cout<<"FS block size entered"<<endl;
    struct stat fi;
    stat("/", &fi);
    // cout<<"Block size of file "<< fi.st_blksize<<endl;
    return fi.st_blksize;
}

// int get_file_size(string file_name)
// {
//     struct stat fi;
//     int rc = stat(file_name.c_str(), &fi);
//     cout<<"File name "<< file_name<<" file size "<<fi.st_size<<endl;
//     return rc == 0 ? fi.st_size : -1;
// }

// Returns file size given file_name
int get_file_size(string file_name)
{
    string file_path = FILE_DIRECTORY + file_name;
    const char *file_path_ = file_path.c_str();
    FILE *fp = fopen(file_path_, "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        exit(0);
    }
    fseek(fp, 0L, SEEK_END);
    int sz = ftell(fp);
    //cout << "File name " << file_name << " file size " << sz << endl;
    fclose(fp);
    return sz;
}

// Creates n_processes
int create_processes(int n_processes)
{
    //cout << "Start Create process pid " << getpid() << endl;
    pid_t pid;
    for (int i = 0; i < n_processes; i++)
    {
        pid = fork();
        if (pid == 0)
        {
            //cout << "Inside Child File idx " << i << endl;
            return i; // child process
        }
        else if (pid < 0)
        {
            //cout << "Fork failed" << endl;
        }
    }
}

// Returns the time to read a block in micro seconds
double start_file_reading()
{
    //cout << "Start file reading pid " << getpid() << endl;
    int file_idx = -1;
    int block_size = get_fs_block_size();
    //cout << "Block size " << block_size << endl;
    file_idx = create_processes(n_processes);
    //cout << "Finish create process pid " << getpid() << endl;
    string file_name = FILE_PREFIX + to_string(file_idx) + FILE_SUFFIX;
    string file_path = FILE_DIRECTORY + file_name;
    //cout << "File name " << file_name << endl;
    Timer t;
    double total_time = 0;
    int file_size = get_file_size(file_name);
    int n_blocks = file_size / block_size;
    // 655 for 64 MB file and 4096B block size
    int read_blocks = n_blocks / 100; // read a fraction of total blocks
    //cout << "Read_blocks " << read_blocks << endl;
    for (int i = 0; i < N_ITERATIONS; i++)
    {
        // DIRECT IO
        // ifstream fin(file_name, ios::in);
        /* must be align in O_DIRECT */
        char *buffer = NULL;
        // https://stackoverflow.com/questions/51993571/how-to-properly-use-posix-memalign
        // https://stackoverflow.com/questions/6001272/how-can-i-read-a-file-with-read-and-o-direct-in-c-on-linux
        // Allocate memory of 2*block size bytes with an alignment of block_size bytes.
        if (posix_memalign((void **)&buffer, 512, block_size))
        {
            cerr << "posix_memalign failed" << endl;
            exit(EXIT_FAILURE);
        }
        // cout<<"Number of blocks "<<n_blocks<<endl;
        int fd;
        if ((fd = open(file_path.c_str(), O_RDONLY | O_DIRECT)) == -1)
        {
            cerr << "File open failed" << endl;
        }
        // POSIX_FADV_DONTNEED attempts to free cached pages associated with the specified region 
        if (posix_fadvise(fd, 0, 0, POSIX_FADV_DONTNEED) < 0)
        {
            cerr << "Setting POSIX flag failed" << endl;
            exit(1);
        }
        int temp;
        t.begin(); // start timer
        for (uint64_t i = 0; i < read_blocks; ++i)
        {
            // read blocks in a random fashion
            temp = pread(fd, buffer, block_size, ((rand() % n_blocks) * block_size));
        }
        t.end(); // end timer
        total_time += (t.time_diff_micro());
        free(buffer);
        if (close(fd) == -1)
        {
            cerr << "Closed file " << file_name << endl;
        }
        // end timer
    }
    //cout << "Process " << getpid() << " ended in " << total_time / N_ITERATIONS << " micro seconds" << endl;
    return total_time / (N_ITERATIONS * read_blocks);
}

int main(int argc, char *argv[])
{
    int status;
    pid_t wpid;
    n_processes = stoi(argv[1]);
    //cout << "Number of processes " << n_processes << endl;
    pid_t parent_pid = getpid();
    //cout << "Parent pid " << parent_pid << endl;
    Stats<double> s(N_RUNS);
    if (getpid() == parent_pid)
    {
        //cout << "Pids " << parent_pid << " " << getpid() << endl;
        s.run_func(start_file_reading);
    }
    if (getpid() == parent_pid)
    {
        // while ((wpid = wait(&status)) > 0)
        //     ;
        cout << "Mean : " << s.mean() << " micro seconds" << endl;
        cout << "Variance : " << s.variance() << " micro seconds" << endl;
        cout << "Median : " << s.median() << " micro seconds" << endl;
        cout << "Std dev : " << s.std_dev() << " micro seconds" << endl;
    }
    return 0;
}