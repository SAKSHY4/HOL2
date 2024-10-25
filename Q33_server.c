/*
============================================================================
Name : Q33_server.c
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

void handle_client(int client_sock) {
    char buffer[256];
    int n;

    // Read data from client
    while ((n = recv(client_sock, buffer, 255, 0)) > 0) {
        buffer[n] = '\0';  // Null terminate the received data
        printf("Received from client: %s", buffer);
        send(client_sock, buffer, n, 0);  // Echo the received data back to the client
    }

    close(client_sock);  // Close the socket
    printf("Client disconnected\n");
}

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // Create a TCP socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("Error opening socket");
        exit(1);
    }

    // Configure server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;  // Accept connections from any address
    server_addr.sin_port = htons(8080);        // Use port 8080

    // Bind the socket
    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error on binding");
        exit(1);
    }

    // Listen for incoming connections
    listen(server_sock, 5);
    printf("Server listening on port 8080\n");

    // Main server loop
    while (1) {
        client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_len);
        if (client_sock < 0) {
            perror("Error on accept");
            exit(1);
        }

        printf("New connection from %s\n", inet_ntoa(client_addr.sin_addr));

        // Handle client in a separate process
        if (fork() == 0) {
            close(server_sock);  // Child closes its copy of the server socket
            handle_client(client_sock);  // Handle client communication
            exit(0);  // Child exits after handling client
        }
        close(client_sock);  // Parent closes its copy of the client socket
    }

    return 0;
}

/*Server listening on port 8080
New connection from 127.0.0.1
Received from client: Hello! The connection was successful
Client disconnected*/