/*
============================================================================
Name : Q29.c
Author : Sakshya Olhan
Description : Write a program to remove the message queue.
Date: 20th Sep, 2024.
============================================================================
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

// Remove a message queue.
int main()
{
    key_t key = ftok(".", 'a');
    int msqid = msgget(key, 0);

    (msgctl(msqid, IPC_RMID, NULL) == -1) ? printf("Delete unsuccessful\n") : printf("Delete successful\n");
    
    return (0);
}

// Delete successful