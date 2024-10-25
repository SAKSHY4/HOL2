/*
============================================================================
Name : Q3.c
Author : Sakshya Olhan
Description :  Write a program to set (any one) system resource limit. Use setrlimit system call.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/resource.h>
#include <errno.h>
#include <string.h>

int main() {
    struct rlimit limit;

    limit.rlim_cur = 1024;
    limit.rlim_max = 2048;

    if (setrlimit(RLIMIT_NOFILE, &limit) == -1) {
        perror("Error setting limits");
        return 1;
    }

    if (getrlimit(RLIMIT_NOFILE, &limit) == 0) {
        printf("New soft limit: %ld\n", (long)limit.rlim_cur);
        printf("New hard limit: %ld\n", (long)limit.rlim_max);
    } else {
        perror("Error getting RLIMIT_NOFILE");
        return 1;
    }

    return 0;
}

/*New soft limit: 1024
New hard limit: 2048*/