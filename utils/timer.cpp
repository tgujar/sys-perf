#include "timer.hpp"
#ifdef CPU_FREQ
#include <stdexcept>

uint64_t Timer::get_start() {
    return ( ((uint64_t)cycles_high << 32) | cycles_low );
}

uint64_t Timer::get_end() {
    return ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
}
uint64_t Timer::diff() {
    return get_end() - get_start(); 
}
double Timer::time_diff_micro() {
    return double(diff()) / CPU_FREQ;
}
double Timer::time_diff_nano() {
    return (double(diff())* 1000) / (CPU_FREQ);
}
#endif