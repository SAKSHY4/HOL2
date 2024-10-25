/*
============================================================================
Name : Q12.c
Author : Sakshya Olhan
Description : Write a program to create an orphan process. Use kill system call to send SIGKILL signal to the parent process from the child process.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main()
{
    // Child Process
    if (!fork())
    {
        sleep(5);
        printf("Child is waiting, pid: %d\n", getpid());
        kill(getppid(), 9);
        printf("Parent process killed\n");
        sleep(10);
    }
    else
    {
        printf("Parent Process, pid: %d\n", getpid());
        sleep(15);
    }

    return 0;
}

/*Parent Process, pid: 1415
Child is waiting, pid: 1416
Parent process killed
Killed*/