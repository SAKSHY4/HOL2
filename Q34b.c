/*
============================================================================
Name : Q34b.c
Author : Sakshya Olhan
Description : Write a program to create a concurrent server.
                a. Use fork
                b. Use pthread_create
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void *handle_client(void *arg) {
    int client_sock = *(int *)arg;
    free(arg);  // Free dynamically allocated memory

    char buffer[256];
    int n;

    // Send welcome message
    char *message = "Welcome to the server!\n";
    send(client_sock, message, strlen(message), 0);

    // Read data from client
    while ((n = recv(client_sock, buffer, 255, 0)) > 0) {
        buffer[n] = '\0';  // Null terminate the received data
        printf("Received from client: %s", buffer);
        send(client_sock, buffer, n, 0);  // Echo the received data back to the client
    }

    close(client_sock);  // Close the socket
    printf("Client disconnected\n");
    return NULL;
}

int main() {
    int server_sock, *client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    pthread_t thread;

    // Create a TCP socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("Error opening socket");
        exit(1);
    }

    // Configure server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);  // Use port 8080

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
        client_sock = malloc(sizeof(int));  // Allocate memory for client socket
        *client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_len);
        if (*client_sock < 0) {
            perror("Error on accept");
            free(client_sock);
            exit(1);
        }

        printf("New connection from %s\n", inet_ntoa(client_addr.sin_addr));

        // Create a new thread to handle the client
        if (pthread_create(&thread, NULL, handle_client, client_sock) != 0) {
            perror("Failed to create thread");
            free(client_sock);  // Free memory on error
            exit(1);
        }

        // Detach the thread so it can clean up after itself
        pthread_detach(thread);
    }

    close(server_sock);
    return 0;
}

/*Server listening on port 8080
New connection from 127.0.0.1
Received from client: Hello from the first client
New connection from 127.0.0.1
Received from client: Hello from the second client
Received from client: First client will now quit
Client disconnected
Received from client: Second client will quit too now
Client disconnected*/