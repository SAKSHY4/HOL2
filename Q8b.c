/*
============================================================================
Name : Q8b.c
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
#include <unistd.h>

void handle_sigint(int sig) {
    printf("Caught SIGINT: Interrupt from keyboard (Ctrl+C)\n");
    exit(0);
}

int main() {
    signal(SIGINT, handle_sigint);

    printf("Running... Press Ctrl+C to stop.\n");
    while (1);

    return 0;
}

//Running... Press Ctrl+C to stop.
// ^CCaught SIGINT: Interrupt from keyboard (Ctrl+C)