/*
============================================================================
Name : Q33_client.c
Author : Sakshya Olhan
Description : Write a program to communicate between two machines using socket.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[256];

    // Create a TCP socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Error opening socket");
        exit(1);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);  // Use port 8080
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);  // Replace with server IP address

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error connecting to server");
        exit(1);
    }

    // Communicate with the server
    while (1) {
        printf("Enter message (or type 'exit' to quit): ");
        fgets(buffer, 255, stdin);
        
        // Exit condition
        if (strncmp(buffer, "exit", 4) == 0) {
            break;
        }

        // Send message to server
        send(sock, buffer, strlen(buffer), 0);

        // Receive echo from server
        int n = recv(sock, buffer, 255, 0);
        buffer[n] = '\0';  // Null terminate the received data
        printf("Echo from server: %s", buffer);
    }

    close(sock);  // Close the socket
    return 0;
}

/*Enter message (or type 'exit' to quit): Hello! The connection was successful
Echo from server: Hello! The connection was successful
Enter message (or type 'exit' to quit): exit*/