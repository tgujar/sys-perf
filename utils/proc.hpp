#pragma once
#include <stdexcept>
#include <sched.h>
#include <unistd.h>
#include <vector>

inline static void use_cores(std::vector<int> cores) {
    cpu_set_t set;
    CPU_ZERO(&set);
    for (auto c: cores) {
        CPU_SET(c, &set);
    }
    if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &set) == -1) {
        throw std::runtime_error("cant set required cores");
    }
}