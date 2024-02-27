#ifndef __bit_operations__
#define __bit_operations__

#include<stdint.h>
#include<iostream>

template<typename T>
bool get_bit(const T num, const int index) {
    bool bit = num & (1 << index);
    return bit;
}

template<typename T>
T set_bit(T num, const int index) {
    T mask = 1 << index;
    return mask | num;
}
#endif
