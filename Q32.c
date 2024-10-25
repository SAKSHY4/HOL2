/*
============================================================================
Name : Q32.c
Author : Sakshya Olhan
Description : Write a program to implement semaphore to protect any critical section.
                a. rewrite the ticket number creation program using semaphore
                b. protect shared memory from concurrent write access
                c. protect multiple pseudo resources ( may be two) using counting semaphore
                d. remove the created semaphore
Date: 20th Sep, 2024.
============================================================================
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

#define SEM_TICKET_UPDATE "/sem_ticket_update"
#define SEM_RESOURCE1 "/sem_resource1"
#define SEM_RESOURCE2 "/sem_resource2"

int main() {
    struct {
        int trainno;
        int tickno;
    } db;

    sem_t *sem_ticket = sem_open(SEM_TICKET_UPDATE, O_CREAT, 0644, 1);
    sem_t *sem_resource1 = sem_open(SEM_RESOURCE1, O_CREAT, 0644, 1);
    sem_t *sem_resource2 = sem_open(SEM_RESOURCE2, O_CREAT, 0644, 1);

    if (sem_ticket == SEM_FAILED || sem_resource1 == SEM_FAILED || sem_resource2 == SEM_FAILED) {
        perror("sem_open failed");
        exit(EXIT_FAILURE);
    }

    int fd = open("record.txt", O_RDWR);
    if (fd < 0) {
        perror("open failed");
        exit(EXIT_FAILURE);
    }

    int train;
    printf("Enter the train no: ");
    scanf("%d", &train);

    printf("Waiting to acquire semaphore for ticket update...\n");
    sem_wait(sem_ticket);
    printf("Semaphore acquired for ticket update\n");

    lseek(fd, (train - 1) * sizeof(db), SEEK_SET);
    read(fd, &db, sizeof(db));

    printf("Number of tickets sold is %d\n", db.tickno);

    db.tickno++;

    lseek(fd, (train - 1) * sizeof(db), SEEK_SET);
    write(fd, &db, sizeof(db));

    printf("Your ticket number is %d\n", db.tickno);

    sem_post(sem_ticket);
    printf("Semaphore released for ticket update\n");

    printf("Accessing resource 1...\n");
    sem_wait(sem_resource1);
    printf("Resource 1 accessed\n");

    printf("Accessing resource 2...\n");
    sem_wait(sem_resource2);
    printf("Resource 2 accessed\n");

    printf("Working on both resources...\n");
    sleep(2);

    sem_post(sem_resource1);
    sem_post(sem_resource2);
    printf("Released both resources\n");

    close(fd);

    printf("Cleaning up semaphores...\n");
    sem_close(sem_ticket);
    sem_close(sem_resource1);
    sem_close(sem_resource2);

    sem_unlink(SEM_TICKET_UPDATE);
    sem_unlink(SEM_RESOURCE1);
    sem_unlink(SEM_RESOURCE2);
    printf("Semaphores removed\n");

    return 0;
}

/*Enter the train no: 2
Waiting to acquire semaphore for ticket update...
Semaphore acquired for ticket update
Number of tickets sold is 1
Your ticket number is 2
Semaphore released for ticket update
Accessing resource 1...
Resource 1 accessed
Accessing resource 2...
Resource 2 accessed
Working on both resources...
Released both resources
Cleaning up semaphores...
Semaphores removed*/