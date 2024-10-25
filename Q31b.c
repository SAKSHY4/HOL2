/*
============================================================================
Name : Q31b.c
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

#define SEM_COUNTING_NAME "/sem_counting"

int main() {
    int initial_count = 2;

    sem_t *sem_counting = sem_open(SEM_COUNTING_NAME, O_CREAT, 0644, initial_count);
    if (sem_counting == SEM_FAILED) {
        perror("Failed to create counting semaphore");
        exit(EXIT_FAILURE);
    }

    printf("Counting semaphore created and initialized to %d\n", initial_count);

    printf("Waiting on counting semaphore (acquiring one resource)...\n");
    sem_wait(sem_counting);
    printf("Acquired one resource\n");

    printf("Waiting on counting semaphore (acquiring one resource)...\n");
    sem_wait(sem_counting);
    printf("Acquired one resource\n");

    printf("Performing work with the resource...\n");
    sleep(2);

    printf("Releasing the resource back to the semaphore...\n");
    sem_post(sem_counting);

    printf("Waiting on counting semaphore (acquiring one resource)...\n");
    sem_wait(sem_counting);
    printf("Acquired one resource\n");

    printf("Performing work with the resource...\n");
    sleep(2);

    printf("Releasing the resource back to the semaphore...\n");
    sem_post(sem_counting);

    printf("Releasing the resource back to the semaphore...\n");
    sem_post(sem_counting);

    sem_close(sem_counting);
    sem_unlink(SEM_COUNTING_NAME);

    printf("Counting semaphore closed and unlinked\n");

    return 0;
}

/*Counting semaphore created and initialized to 2
Waiting on counting semaphore (acquiring one resource)...
Acquired one resource
Waiting on counting semaphore (acquiring one resource)...
Acquired one resource
Performing work with the resource...
Releasing the resource back to the semaphore...
Waiting on counting semaphore (acquiring one resource)...
Acquired one resource
Performing work with the resource...
Releasing the resource back to the semaphore...
Releasing the resource back to the semaphore...
Counting semaphore closed and unlinked*/