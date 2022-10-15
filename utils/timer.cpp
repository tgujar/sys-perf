#include "timer.hpp"

uint64_t Timer::get_start() {
    return ( ((uint64_t)cycles_high << 32) | cycles_low );
}

uint64_t Timer::get_end() {
    return ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
}
uint64_t Timer::diff() {
    return get_end() - get_start(); 
}