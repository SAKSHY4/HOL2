/*
============================================================================
Name : Q28.c
Author : Sakshya Olhan
Description : Write a program to change the exiting message queue permission. (Use msqid_ds structure)
Date: 20th Sep, 2024.
============================================================================
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

int main()
{
    key_t key = ftok(".", 'a');
    int msqid = msgget(key, IPC_CREAT | 0666);
    struct msqid_ds st_to_set;
    struct msqid_ds st_to_read;

    msgctl(msqid, IPC_STAT, &st_to_read);
    printf("Current access Permissions - %o\n", st_to_read.msg_perm.mode);

    st_to_set.msg_perm.mode = 0777;
    msgctl(msqid, IPC_SET, &st_to_set);
    msgctl(msqid, IPC_STAT, &st_to_read);
    printf("New access Permissions - %o\n", st_to_read.msg_perm.mode);
    return (0);
}

/*[sudo] password for binod: 
Current access Permissions - 666
New access Permissions - 777*/