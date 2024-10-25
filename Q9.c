/*
============================================================================
Name : Q9.c
Author : Sakshya Olhan
Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal - Use signal system call.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void ignore_sigint(int sig) {
    printf("SIGINT signal ignored!\n");
}

int main() {
    printf("Ignoring SIGINT signal for 10 seconds. Press Ctrl+C...\n");
    signal(SIGINT, ignore_sigint);

    sleep(5);

    printf("\nResetting SIGINT signal to default action. Press Ctrl+C now...\n");
    signal(SIGINT, SIG_DFL);

    sleep(5);

    printf("No SIGINT received. Exiting normally.\n");
    return 0;
}

/*Ignoring SIGINT signal for 10 seconds. Press Ctrl+C...
^CSIGINT signal ignored!

Resetting SIGINT signal to default action. Press Ctrl+C now...
^C*/