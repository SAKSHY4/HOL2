/*
============================================================================
Name : Q8e.c
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
#include <sys/time.h>
#include <unistd.h>

void handle_sigalrm(int sig) {
    printf("Caught SIGALRM: Timer expired\n");
}

int main() {
    struct itimerval timer;

    signal(SIGALRM, handle_sigalrm);

    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 1;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    setitimer(ITIMER_REAL, &timer, NULL);

    return 0;
}

// Caught SIGALRM: Timer expired