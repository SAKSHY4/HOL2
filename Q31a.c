/*
============================================================================
Name : Q31a.c
Author : Sakshya Olhan
Description : Write a program to create a semaphore and initialize value to the semaphore.
                i.  Create a binary semaphore
                ii. Create a counting semaphore
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

#define SEM_BINARY_NAME "/sem_binary"

int main() {

    sem_t *sem_binary = sem_open(SEM_BINARY_NAME, O_CREAT, 0644, 1);
    if (sem_binary == SEM_FAILED) {
        perror("Failed to create binary semaphore");
        exit(EXIT_FAILURE);
    }

    printf("Binary semaphore created and initialized to 1 (unlocked)\n");

    printf("Waiting on binary semaphore (acquiring lock)...\n");
    sem_wait(sem_binary);
    printf("Binary semaphore locked\n");

    printf("Performing some critical section work...\n");
    sleep(2);

    printf("Releasing binary semaphore (unlocking)...\n");
    sem_post(sem_binary);

    sem_close(sem_binary);
    sem_unlink(SEM_BINARY_NAME);

    printf("Binary semaphore closed and unlinked\n");

    return 0;
}

/*Binary semaphore created and initialized to 1 (unlocked)
Waiting on binary semaphore (acquiring lock)...
Binary semaphore locked
Performing some critical section work...
Releasing binary semaphore (unlocking)...
Binary semaphore closed and unlinked*/