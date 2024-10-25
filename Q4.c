/*
============================================================================
Name : Q4.c
Author : Sakshya Olhan
Description :  Write a program to measure how much time is taken to execute 100 getppid() system call. Use time stamp counter.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

static inline uint64_t rdtsc() {
    unsigned int lo, hi;
    asm volatile("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

int main() {
    uint64_t start, end;
    int i;

    start = rdtsc();

    for (i = 0; i < 100; i++) {
        getppid();
    }

    end = rdtsc();

    uint64_t total_cycles = end - start;
    printf("CPU cycles for 100 getppid() calls: %lu\n", total_cycles);

    return 0;
}

// CPU cycles for 100 getppid() calls: 12484