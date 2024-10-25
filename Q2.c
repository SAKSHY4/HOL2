/*
============================================================================
Name : Q2.c
Author : Sakshya Olhan
Description :  Write a program to print the system resource limits. Use getrlimit system call.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/resource.h>
#include <errno.h>
#include <string.h>

void print_limit(int resource, const char *name) {
    struct rlimit limit;

    if (getrlimit(resource, &limit) == 0) {
        printf("%-20s: Soft limit = %ld, Hard limit = %ld\n", name, (long)limit.rlim_cur, (long)limit.rlim_max);
    } else {
        printf("Error getting %s: %s\n", name, strerror(errno));
    }
}

int main() {

    print_limit(RLIMIT_CPU, "CPU Time");
    print_limit(RLIMIT_FSIZE, "File Size");
    print_limit(RLIMIT_DATA, "Data Segment Size");
    print_limit(RLIMIT_STACK, "Stack Size");
    print_limit(RLIMIT_CORE, "Core File Size");
    print_limit(RLIMIT_RSS, "Resident Set Size");
    print_limit(RLIMIT_NOFILE, "Number of Open Files");
    print_limit(RLIMIT_AS, "Address Space Size");
    print_limit(RLIMIT_NPROC, "Number of Processes");
    print_limit(RLIMIT_MEMLOCK, "Locked Memory Size");
    print_limit(RLIMIT_LOCKS, "File Locks");

    return 0;
}

/*CPU Time            : Soft limit = -1, Hard limit = -1
File Size           : Soft limit = -1, Hard limit = -1
Data Segment Size   : Soft limit = -1, Hard limit = -1
Stack Size          : Soft limit = 8388608, Hard limit = -1
Core File Size      : Soft limit = 0, Hard limit = -1
Resident Set Size   : Soft limit = -1, Hard limit = -1
Number of Open Files: Soft limit = 1048576, Hard limit = 1048576
Address Space Size  : Soft limit = -1, Hard limit = -1
Number of Processes : Soft limit = 31261, Hard limit = 31261
Locked Memory Size  : Soft limit = 67108864, Hard limit = 67108864
File Locks          : Soft limit = -1, Hard limit = -1*/