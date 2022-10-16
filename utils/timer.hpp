#pragma once
#ifdef CPU_FREQ
#include <cinttypes>

class Timer {
    unsigned cycles_low, cycles_high, cycles_low1, cycles_high1;

    public: 
        Timer() {}
        inline void begin() {
             asm volatile ("CPUID\n\t" "RDTSC\n\t"
                       "mov %%edx, %0\n\t"
                       "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
                        "%rax", "%rbx", "%rcx", "%rdx");
        }

        inline void end() {
            asm volatile("RDTSCP\n\t"
                        "mov %%edx, %0\n\t" "mov %%eax, %1\n\t"
                        "CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
                        "%rax", "%rbx", "%rcx", "%rdx");
        }
        uint64_t get_start();
        uint64_t get_end();
        uint64_t diff();
        double time_diff_micro();
};
#endif