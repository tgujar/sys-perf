#include <iostream>
#include <vector>
#include <map>
#include "proc.hpp"
#include "timer.hpp"
#include "stats.hpp"
using namespace std;

vector<int> array_sizes; // in bytes
vector<int> strides;
const int N_RUNS = 3;
const int N_LOADS = 1000000;

double memory_access_time_given_stride_arraysize(int mem[], int array_size, int stride)
{
    Timer t;
    int count = N_LOADS;
    int idx = 0;
    t.begin();
    while (count)
    {
        // int y = mem[idx];
        // idx = (idx + stride) % array_size;
        // count--;
        idx = mem[idx];
        count--;
    }
    t.end();
    return t.time_diff_nano() / N_LOADS;
}

map<int, double> memory_access_time_fixed_array_size(int array_size)
{
    map<int, double> times;
    int *mem = new int[array_size];
    for (int j = 0; j < strides.size(); j++)
    {
        double time = memory_access_time_given_stride_arraysize(mem, array_size, strides[j]);
        times[strides[j]] = time;
    }
    delete[] mem;
    return times;
}

map<int, double> memory_access_time_fixed_stride(int stride)
{
    map<int, double> times;
    // Stats<double> s(N_RUNS);
    for (int j = 0; j < array_sizes.size(); j++)
    {
        double mean = 0.0;
        for (int i = 0; i < N_RUNS; i++)
        {
            int *mem = new int[array_sizes[j]];
            for (int k = 0; k < array_sizes[j]; k++)
            {
                mem[k] = (k + stride) % array_sizes[j];
            }
            mean += memory_access_time_given_stride_arraysize(mem, array_sizes[j], stride);
            delete[] mem;
        }
        times[array_sizes[j]] = mean / N_RUNS;
        // for (int i = 0; i < array_sizes[j]; i++)
        // {
        //     int bucket = (i/stride)*stride;
        //     int offset = rand() % array_sizes[j];
        //     // randomly assigning indices to have cache misses
        //     mem[i] = (bucket + offset) % array_sizes[j];
        // }
        // double time = memory_access_time_given_stride_arraysize(mem, array_sizes[j], stride);
        // delete[] mem;
        // s.reset_vals();
    }
    return times;
}

map<pair<int, int>, double> memory_access_time()
{
    map<pair<int, int>, double> times; // {array_size, stride} -> time
    for (int i = 0; i < strides.size(); i++)
    {
        map<int, double> times_fixed_array = memory_access_time_fixed_stride(strides[i]);
        for (auto item : times_fixed_array)
        {
            times[{item.first, strides[i]}] = item.second;
        }
    }
    return times;
}

int main()
{
    use_cores(vector<int>{0}); // force process to use only single core

    for (int i = 11; i <= 30; i++)
    {
        int sz = (1 << i) / sizeof(int);
        array_sizes.push_back(sz);
    }
    strides = {64, 128, 256, 512, 1024, 2048, 4096, 8192};

    // for (int i = 0; i < array_sizes.size(); i++)
    // {
    //     map<int, double> times_fixed_array = memory_access_time_fixed_array_size(array_sizes[i]);
    //     for (auto item : times_fixed_array)
    //     {
    //         times[{array_sizes[i], item.first}] = item.second;
    //     }
    // }
    map<pair<int, int>, double> times = memory_access_time();
    for (auto item : times)
    {
        int array_size = item.first.first;
        int stride = item.first.second;
        double time = item.second;
        // cout << "Array size " << array_size << ", stride " << stride << ", time " << time << endl;
        cout << array_size << " " << stride << " " << time << endl;
    }
    return 0;
}