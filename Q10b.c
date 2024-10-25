/*
============================================================================
Name : Q10b.c
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

void handle_sigint(){
    write(STDOUT_FILENO, "Caught SIGINT\n", 14);
    exit (0);
}

int main(){

    struct sigaction sa;
    sa.sa_handler = handle_sigint;
    sa.sa_flags = 0;

    printf("Send SIGINT (Ctrl+C)\n");
    while (1)
    if (sigaction(SIGINT, &sa, NULL) == -1)
        perror("Sigaction Failed!\n");
    
    return 0;
}

/*Send SIGINT (Ctrl+C)
^CCaught SIGINT*/