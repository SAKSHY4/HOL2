/*
============================================================================
Name : Q5.c
Author : Sakshya Olhan
Description :  Write a program to print the system limitation of
				i. Maximum length of the arguments to the exec family of functions.
				ii. Maximum number of simultaneous process per user id.
				iii. Number of clock ticks (jiffy) per second.
				iv. Maximum number of open files
				v. Size of a page
				vi. Total number of pages in the physical memory
				vii. Number of currently available pages in the physical memory.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/sysinfo.h>

int main() {
    // a.
    long arg_max = sysconf(_SC_ARG_MAX);
    printf("Maximum length of arguments to exec functions: %ld\n", arg_max);

    // b.
    long max_procs = sysconf(_SC_CHILD_MAX);
    printf("Maximum number of simultaneous processes per user ID: %ld\n", max_procs);

    // c.
    long clock_ticks = sysconf(_SC_CLK_TCK);
    printf("Number of clock ticks (jiffy) per second: %ld\n", clock_ticks);

    // d.
    long open_max = sysconf(_SC_OPEN_MAX);
    printf("Maximum number of open files: %ld\n", open_max);

    // e.
    long page_size = sysconf(_SC_PAGESIZE);
    printf("Size of a page: %ld bytes\n", page_size);

    // f.
    struct sysinfo info;
    sysinfo(&info);
    printf("Total number of pages in physical memory: %ld\n", info.totalram / page_size);

    // g.
    printf("Number of currently available pages in physical memory: %ld\n", (info.totalram - info.freeram) / page_size);

    return 0;
}

/*Maximum length of arguments to exec functions: 2097152
Maximum number of simultaneous processes per user ID: 31261
Number of clock ticks (jiffy) per second: 100
Maximum number of open files: 1048576
Size of a page: 4096 bytes
Total number of pages in physical memory: 2002441
Number of currently available pages in physical memory: 1753353*/