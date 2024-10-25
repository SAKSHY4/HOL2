/*
============================================================================
Name : Q30.c
Author : Sakshya Olhan
Description : Write a program to create a shared memory. 
    1. Write some data to the shared memory
    2. Attach with `O_RDONLY` and check whether you are able to overwrite. 
    3. Detach the shared memory 
    4. Remove the shared memory
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

#define SHM_NAME "/my_shared_memory"
#define SHM_SIZE 1024

int main() {

    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open failed");
        exit(EXIT_FAILURE);
    }

    if (ftruncate(shm_fd, SHM_SIZE) == -1) {
        perror("ftruncate failed");
        exit(EXIT_FAILURE);
    }

    // Map the shared memory into the process's address space (read-write)
    void *shm_ptr = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("mmap failed");
        exit(EXIT_FAILURE);
    }

    char *message = "Hello, this is some data in shared memory!";
    printf("Writing data to shared memory: %s\n", message);
    snprintf((char *)shm_ptr, SHM_SIZE, "%s", message);

    // Unmap from the shared memory
    if (munmap(shm_ptr, SHM_SIZE) == -1) {
        perror("munmap failed");
        exit(EXIT_FAILURE);
    }

    printf("Data written and shared memory detached from (read-write mode)\n");

    // Attach to the shared memory with read-only access
    shm_ptr = mmap(0, SHM_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("mmap read-only failed");
        exit(EXIT_FAILURE);
    }

    printf("Attempting to overwrite the data in read-only mode...\n");
    char *read_only_message = (char *)shm_ptr;

    // snprintf(read_only_message, SHM_SIZE, "Trying to overwrite...");

    printf("Data from shared memory (read-only): %s\n", read_only_message);

    if (munmap(shm_ptr, SHM_SIZE) == -1) {
        perror("munmap failed");
        exit(EXIT_FAILURE);
    }

    printf("Shared memory detached from (read-only mode)\n");

    close(shm_fd);

    if (shm_unlink(SHM_NAME) == -1) {
        perror("shm_unlink failed");
        exit(EXIT_FAILURE);
    }

    printf("Shared memory removed\n");

    return 0;
}

/*Writing data to shared memory: Hello, this is some data in shared memory!
Data written and shared memory detached from (read-write mode)
Attempting to overwrite the data in read-only mode...
Data from shared memory (read-only): Hello, this is some data in shared memory!
Shared memory detached from (read-only mode)
Shared memory removed*/