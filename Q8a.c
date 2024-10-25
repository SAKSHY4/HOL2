/*
============================================================================
Name : Q8a.c
Author : Sakshya Olhan
Description :  Write a separate program using signal system call to catch the following signals.
                i. SIGSEGV
                ii. SIGINT
                iii. SIGFPE
                iv. SIGALRM (use alarm system call)
                v. SIGALRM (use setitimer system call)
                vi. SIGVTALRM (use setitimer system call)
                vii. SIGPROF (use setitimer system call)
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void handle_sigsegv(int sig) {
    printf("Caught SIGSEGV: Segmentation Fault\n");
    exit(1);
}

int main() {
    signal(SIGSEGV, handle_sigsegv);

    int *ptr = NULL;
    *ptr = 42;

    return 0;
}

//Caught SIGSEGV: Segmentation Fault