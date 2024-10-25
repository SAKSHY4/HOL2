#include <stdio.h>
/*
============================================================================
Name : Q8f.c
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

#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void handle_sigvtalrm(int sig) {
    printf("Caught SIGVTALRM: Virtual timer expired\n");
}

int main() {
    struct itimerval timer;

    signal(SIGVTALRM, handle_sigvtalrm);

    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 1;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    setitimer(ITIMER_VIRTUAL, &timer, NULL);
    while(1);

    return 0;
}

// Caught SIGVTALRM: Virtual timer expired