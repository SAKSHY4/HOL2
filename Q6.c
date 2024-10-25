/*
============================================================================
Name : Q6.c
Author : Sakshya Olhan
Description :  Write a simple program to create three threads.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* thread_function(void* arg) {
    int thread_num = *((int*)arg);
    printf("Thread %d executing\n", thread_num);
    return NULL;
}

int main() {
    pthread_t threads[3];
    int thread_nums[3];

    for (int i = 0; i < 3; i++) {
        thread_nums[i] = i + 1;
        if (pthread_create(&threads[i], NULL, thread_function, &thread_nums[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads finished execution\n");
    return 0;
}

/*Thread 1 executing
Thread 3 executing
Thread 2 executing
All threads finished execution*/