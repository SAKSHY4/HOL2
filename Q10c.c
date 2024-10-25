/*
============================================================================
Name : Q10c.c
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

void handle_sigfpe() {
    write(STDOUT_FILENO, "Caught SIGFPE\n", 14);
    exit(0);
}

int main()
{
    struct sigaction sa;

    sa.sa_handler = handle_sigfpe;
    sa.sa_flags = 0;

    if (sigaction(SIGFPE, &sa, NULL) == -1)
        perror("Sigaction failed!");
    
    int a = 5 / 0;

    return 0;
}

// Caught SIGFPE