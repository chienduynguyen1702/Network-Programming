#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define GET_FILE_BUFFER 255


int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <IP_Addr> <Port_Number>\n", argv[0]);
        exit(1);
    }
    const char *ip_addr = argv[1];
    int port = atoi(argv[2]);

    int client_socket;
    struct sockaddr_in server_addr;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0)
    {
        perror("Error creating socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip_addr, &(server_addr.sin_addr));

    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Error connecting to server");
        exit(1);
    }

    char welcome_message[BUFFER_SIZE] = {0};
    recv(client_socket, welcome_message, sizeof(welcome_message), 0);
    printf("%s\n", welcome_message);

    char file_contents[BUFFER_SIZE];

    char file_path[BUFFER_SIZE];
    char message_result[BUFFER_SIZE];

    while (1)
    {
        FILE *file;
        int file_size = 0;
        printf("\nEnter file path (or leave empty to exit): ");
        fflush(stdin);
        fgets(file_path, sizeof(file_path), stdin);
        if (strcmp(file_path, "\n") == 0) {
            printf("Empty input !!\n");
            break;
        }
        // remove newline character from file_path
        file_path[strcspn(file_path, "\n")] = 0;
        if (strlen(file_path) == 0)
        {
            break;
        }
        // printf("\n");

        file = fopen(file_path, "rb");
        if (NULL == file)
        {
            printf("file can't be opened \n");
        }
        while (fgets(file_contents, GET_FILE_BUFFER, file) != NULL)
        {
            file_size += strlen(file_contents);
        }
        fseek(file, 0, SEEK_SET);

        // printf("\n");

        char upload_message[BUFFER_SIZE+8];
        snprintf(upload_message, sizeof(upload_message),"UPLD %s %d", file_path, file_size);


        // check if upload_message length is too long
        if (strlen(upload_message) >= BUFFER_SIZE)
        {
            fprintf(stderr, "Error: Path too long\n");
            exit(1);
        }
        send(client_socket, upload_message, strlen(upload_message), 0);

        recv(client_socket, message_result, sizeof(message_result), 0);

        // Received message from server
        printf("\n%s\n", message_result);
        // printf("\n================================================\n\n");

        char buffer[BUFFER_SIZE];
        size_t bytesRead;
        // while (fgets(file_contents, GET_FILE_BUFFER, file) != NULL)
        while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0)
        {
            // char *lastNewline = strrchr(buffer, '\n');

            // // If a newline character is found, terminate the string there
            // if (lastNewline != NULL)
            // {
            //     *lastNewline = '\0';
            // }

            // printf("sending : '%s', %ld\n", buffer, bytesRead);
            // sleep(2);
            send(client_socket, buffer, bytesRead, 0);

        }
        // printf("================================================\n\n");
        // done sending file
        // printf("done sending file\n");
        send(client_socket, "FileTransferComplete", strlen("FileTransferComplete"), 0);
        // send file contents to server
        // send_file_contents(client_socket, file_path);

        char upload_result[BUFFER_SIZE];
        recv(client_socket, upload_result, sizeof(upload_result), 0);
        printf("%s\n\n", upload_result);
        printf("================================================\n\n");
        fclose(file);
    }
        printf("================================================\n\n");
    printf("Goodbye!\n");
    close(client_socket);

    return 0;
}
