/*
============================================================================
Name : Q10a.c
Author : Sakshya Olhan
Description : Write a separate program using sigaction system call to catch the following signals.
                i.   SIGSEGV
                ii.  SIGINT
                iii. SIGFPE
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigsegv() {
    write(STDOUT_FILENO, "Caught SIGSEGV\n", 14);
    exit(0);
}

int main() {
    struct sigaction sa;

    sa.sa_handler = handle_sigsegv;
    sa.sa_flags = 0;
    
    if (sigaction(SIGSEGV, &sa, NULL) == -1) {
        perror("sigaction failed!");
        exit(EXIT_FAILURE);
    }

    int *p = NULL;
    *p = 0;

    return 0;
}

/*Caught SIGSEGV*/