#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define NOT_FOUND 0
#define FOUND 1
#define FALSE 0
#define TRUE 1

#include "lib/logger.h"

struct ClientHandlerArgs {
    int client_socket;
    const char *directory;
    const char *ip_addr;
    int server_socket;
};


int parseMessage(char *message, char **command, char **fileName, int *charCount)
{
    *command = strtok(message, " ");
    if (*command == NULL)
        return 0; // Return 0 if command is NULL

    *fileName = strtok(NULL, " ");
    if (*fileName == NULL)
        return 0; // Return 0 if fileName is NULL

    char *charCountStr = strtok(NULL, " ");
    if (charCountStr == NULL)
        return 0; // Return 0 if charCountStr is NULL

    *charCount = atoi(charCountStr);
    return 1; // Return 1 for success
}

void printMessage(char *command, char *fileName, int charCount)
{
    printf("\nCommand: %s\n", command);
    printf("File name: %s\n", fileName);
    printf("Character count in file: %d\n", charCount);
}

void *client_handler(void *arg)
{
    if (arg == NULL) {
        // Handle the case where arg is NULL (i.e., an error occurred)
        return NULL;
    }
        struct ClientHandlerArgs *args = (struct ClientHandlerArgs *)arg;
    int server_socket = args->server_socket;
    int client_socket = args->client_socket;
    const char *directory = args->directory;
    const char *ip_addr = args->ip_addr;
    // printf("Client connected in %d \n", server_socket);
    // int client_socket = *((int *)arg);
    // printf("Client connected in %d \n", client_socket);
    // printf("directory: %s\n", directory);
    char welcome_message[BUFFER_SIZE] = "+OK Welcome to file server";
    send(client_socket, welcome_message, sizeof(welcome_message), 0);
        logger_connect(welcome_message,ip_addr,server_socket);
    // printf("\n================================================\n\n");

    while (1)
    {
        // message
        char *command;
        char *fileName;

        char filePath[BUFFER_SIZE];
        char message[BUFFER_SIZE] = {0};
        int charCount;
        FILE *file;
        char inputlog[BUFFER_SIZE];
        int bytesReceived = recv(client_socket, message, sizeof(message), 0);
        // printf("received message : \'%s\'\n\n", message);
        // printf("bytesReceived : %d\n\n", bytesReceived);
        strcpy(inputlog, message);
        if (bytesReceived == 0) {
            printf("Client disconnected\n");
            break;
        }
        // if (bytesReceived > 0)
        // printf("\n================================================\n");
                    // printf("check!!!!!!!!!!!!!!!\n");sleep(2);
        if (parseMessage(message, &command, &fileName, &charCount)) // if return 1
        {

            // printMessage(command, fileName, charCount);
            // printf("File name: %s\n", fileName);
            // printf("directory: %s\n", directory);
            sprintf(filePath, "%s/%s", directory, fileName);
            // printf("File path: %s\n", filePath);
            file = fopen(filePath, "wb");
            if (file == NULL)
            {
                perror("Error opening file");
                exit(1);
            }
            send(client_socket, "+OK Please send file", sizeof("+OK Please send file"), 0);
            // send(client_socket, "adudcmaovcl", sizeof("adudcmaovcl"), 0);
            int receiving = 1;

            int totalBytesReceived = 0;
            while (receiving)
            {   
                // // printf("received file : ");
                // char fileContents[BUFFER_SIZE];
                // int bytesReceived = recv(client_socket, fileContents, BUFFER_SIZE, 0);
                // // printf("%d\n", bytesReceived);
                // if (bytesReceived <= 0)
                // {
                //     perror("Error receiving file");
                //     // receiving = 0;// Exit the loop if no more data is received
                //     break;
                // }
                // // fileContents[bytesReceived] = '\0'; // Add null-terminator
                // if (strcmp(fileContents, "FileTransferComplete") != 0)
                // {
                //     fwrite(fileContents, 1, bytesReceived, file);

                // }
                // else
                //     receiving = 0;

                 // printf("received file : ");
                // char fileContents[BUFFER_SIZE];
                int bytesToReceive = charCount;
                while (bytesToReceive > 0)
                {
                    char fileContents[charCount];
                    // int bytesToReceive = charCount;

                    int ret = recv(client_socket, fileContents, charCount, MSG_WAITALL);
                    printf("ret : %d\n", ret);
                    // printf("fileContents : \'%s\'\n", fileContents);
                    if (ret <= 0)
                    {
                        if (ret == 0)
                        {
                            printf("Client disconnected\n");
                        }
                        else
                        {
                            perror("Error receiving file");
                        }
                        receiving = 0; // Exit the loop if no more data is received
                        break;
                    }

                    if (strcmp(fileContents, "FileTransferComplete") == 0)
                    {
                        break; // Exit the loop when transfer is complete
                    }

                    fwrite(fileContents, 1, ret, file);
                    bytesToReceive -= ret;
                    totalBytesReceived += ret;

                }
                fclose(file);
                printf("Finished receive file\n");
                receiving=0;
                send(client_socket, "+OK Successful upload", sizeof("+OK Successful upload"), 0);
            
            }
        logger_file_tranfer(inputlog,ip_addr,server_socket, FOUND, NULL);
        }
        else // if return 0
        {
            // printf("Failed to parse message\n");
            // printf("Command: %s\n", command);
            // printf("File Name: %s\n", fileName);
            // printf("Character Count: %d\n", charCount);

        }
        // printf("\n================================================\n");
    }
    // pthread_exit(NULL);
    // close(client_socket);
    return NULL;
    // printf("Client closed %d \n", client_socket);
}

int main(int argc, char *argv[])
{
    // if (argc != 3)
    // {
    //     printf("Usage: %s <Port_Number> <Directory_name>\n", argv[0]);
    //     exit(1);
    // }

    int port = atoi(argv[1]);
    const char *directory = argv[2];
    // char message[BUFFER_SIZE];
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
    {
        perror("Error creating socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Error binding socket");
        exit(1);
    }

    if (listen(server_socket, 10) == 0)
    {
        printf("Server listening on port %d\n", port);
    }
    else
    {
        perror("Error listening on socket");
        exit(1);
    }

    addr_size = sizeof(client_addr);

    // char buffer[BUFFER_SIZE];

    while (1)
    {
        struct ClientHandlerArgs *args = malloc(sizeof(struct ClientHandlerArgs));
        args->directory = directory;
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_size);
        // printf("Client connected in %d \n", client_socket);
        // printf("server_socket connected in %d \n", port);
        args->client_socket = client_socket;
        args->ip_addr = inet_ntoa(client_addr.sin_addr);
        args->server_socket = port;
        if (args->client_socket < 0)
        {
            perror("Error accepting client");
            free(args); // Giải phóng bộ nhớ khi không thể kết nối
            continue;
        }
        pthread_t tid;
        if (pthread_create(&tid, NULL, client_handler,  (void *)args)!= 0)
        {
            perror("Error creating thread");
            free(args); // Giải phóng bộ nhớ khi không thể tạo luồng
            close(args->client_socket);
        }
        pthread_detach(tid);
    }

    close(server_socket);

    return 0;
}
