/*
============================================================================
Name : Q7.c
Author : Sakshya Olhan
Description : Write a simple program to print the created thread IDs.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* thread_function(void* arg) {
    printf("Thread ID: %lu\n", pthread_self());
    return NULL;
}

int main() {
    pthread_t threads[3];

    for (int i = 0; i < 3; i++) {
        if (pthread_create(&threads[i], NULL, thread_function, NULL) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads have completed.\n");

    return 0;
}

/*Thread ID: 139707132462784
Thread ID: 139707124070080
Thread ID: 139707115677376
All threads have completed.*/