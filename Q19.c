/*
============================================================================
Name : Q19.c
Author : Sakshya Olhan
Description : Create a FIFO file by
                i. mknod command
                ii. mkfifo command
                iii. Use strace command to find out, which command (mknod or mkfifo) is better.
                iv. mknod system call
                v. mkfifo library function
Date: 20th Sep, 2024.
============================================================================
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

int main()
{
    char name[40];
    printf("Enter the name of fifo file: ");
    scanf("%s", name);

    int choice;
    printf("Choose an option:\n1.) mknod system call\n2.) mkfifo system call\n=> ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        printf("Using mknod system call...\n");

        if (mknod(name, __S_IFIFO | 0744, 0) == -1)
        {
            perror("Error: ");
            return -1;
        }
        printf("FIFO file created using mknod\n");
        break;
    case 2:
        printf("Using mkfifo system call...\n");

        if (mkfifo(name, 0744) == -1)
        {
            perror("Error: ");
            return -1;
        }
        printf("FIFO file created using mkfifo\n");
        break;

    default:
        printf("Invalid choice\n");
        break;
    }

    return (0);
}

/*Enter the name of fifo file: FIFO
Choose an option:
1.) mknod system call
2.) mkfifo system call
=> 2
Using mkfifo system call...
FIFO file created using mkfifo*/