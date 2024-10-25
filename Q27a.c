/*
============================================================================
Name : Q27a.c
Author : Sakshya Olhan
Description : Write a program to receive messages from the message queue with `0` as a flag
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct MyMessage {
    long mtype;
    int data;
};

int main() {
    int key = ftok("Example", 'a');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    int msgid = msgget(key, IPC_CREAT | 0744);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Key=0x%0x\nmsgid=%d\n", key, msgid);

    struct MyMessage content;
    content.mtype = 1;
    content.data = 100;

    if (msgsnd(msgid, &content, sizeof(content.data), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }

    printf("Message sent! Data = %d\n", content.data);

    return 0;
}

/*Key=0x6120323b
msgid=0
Message sent! Data = 100*/