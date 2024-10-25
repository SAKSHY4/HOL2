/*
============================================================================
Name : Q11.c
Author : Sakshya Olhan
Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal - use sigaction system call.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigint()
{
    write(STDOUT_FILENO, "Caught SIGINT\n", 14);
}

int main()
{
    struct sigaction sa;

    sa.sa_handler = handle_sigint;
    sa.sa_flags = 0;

    printf("Enter Ctrl+C\n");

    if(sigaction(SIGINT, &sa, NULL) == -1)
        perror ("Error calling sigaction");
    
    pause();

    sa.sa_handler = SIG_DFL;
    
    printf("Enter Ctrl+C again\n");

    if(sigaction(SIGINT, &sa, NULL) == -1)
        perror ("Error calling sigaction");
    
    pause();

    return 0;    
}

/*Enter Ctrl+C
^CCaught SIGINT
Enter Ctrl+C again
^C*/