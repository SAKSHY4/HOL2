/*
============================================================================
Name : Q1c_us.c
Author : Sakshya Olhan
Description :   Write a separate program (for each time domain) to set a interval timer in 10s and 10ms
                c. ITIMER_PROF
Date: 20th Sep, 2024.
============================================================================
*/

#include <sys/time.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handle_signal(int signum) {
    printf("Received SIGPROF signal\n");
}

int main() {
    signal(SIGPROF, handle_signal);

    struct itimerval timer;

    timer.it_value.tv_sec = 2;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 10;

    if (setitimer(ITIMER_PROF, &timer, NULL) == -1) {
        perror("Error setting ITIMER_PROF");
    }

    while (1);

    return 0;
}

//Received SIGPROF signal