/*
============================================================================
Name : Q1a_us.c
Author : Sakshya Olhan
Description :   Write a separate program (for each time domain) to set a interval timer in 10s and 10ms
                a. ITIMER_REAL
Date: 20th Sep, 2024.
============================================================================
*/

#include <sys/time.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handle_signal(int signum) {
    printf("Received SIGALRM signal\n");
}

int main() {
    signal(SIGALRM, handle_signal);

    struct itimerval timer;

    timer.it_value.tv_sec = 2;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 10;

    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("Error setting ITIMER_REAL");
    }

    while (1) {
        pause();
    }

    return 0;
}

//Received SIGALRM signal