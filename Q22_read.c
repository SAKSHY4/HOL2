/*
============================================================================
Name : Q22_read.c
Author : Sakshya Olhan
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select system call with FIFO.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>


int main() {
    fd_set rfds;
    struct timeval tv;
    int fd;

    tv.tv_sec = 10;

    fd = open("FIFO", O_RDONLY | O_CREAT);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    FD_ZERO(&rfds);
    FD_SET(fd, &rfds);

    if (!select(fd + 1, &rfds, NULL, NULL, &tv)) {
        printf("No data available\n");
    }
	
else{

    char buffer[100];
    
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer));

    if (bytesRead == -1) {
        perror("read");
        close(fd);
        return 1;
    }

    close(fd);
    
    printf("Data read from FIFO: %s\n", buffer);


}
    close(fd);

    return 0;
}

/*Data read from FIFO: Hello! This is a message from the writer program*/