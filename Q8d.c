/*
============================================================================
Name : Q8d.c
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
#include <unistd.h>

void handle_sigalrm(int sig) {
    printf("Caught SIGALRM: Alarm triggered\n");
}

int main() {
    signal(SIGALRM, handle_sigalrm);

    alarm(1);
    pause();

    return 0;
}

// Caught SIGALRM: Alarm triggered