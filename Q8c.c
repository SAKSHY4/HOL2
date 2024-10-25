/*
============================================================================
Name : Q8c.c
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

void handle_sigfpe(int sig) {
    printf("Caught SIGFPE: Floating-point exception\n");
    exit(1);
}

int main() {
    signal(SIGFPE, handle_sigfpe);

    int a = 0;
    int b = 0;
    b = b/a;

    return 0;
}

// Caught SIGFPE: Floating-point exception