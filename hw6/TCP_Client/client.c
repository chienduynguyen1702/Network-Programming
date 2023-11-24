#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "./lib/response.h"

#define MAX_BUFFER_SIZE 1024
#define MAX_INPUT_SIZE 1010
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <IP_Addr> <Port_Number>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serv_addr;
    int sock = 0;
    char buffer[MAX_BUFFER_SIZE] = {0};
    // char *hello = "Hello from client";

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        exit(EXIT_FAILURE);
    }
    int menu=-1;
    char returnCode[10]={0};
    // recv(sock, returnCode, sizeof(int), 0);
    if(read(sock, returnCode, sizeof(returnCode))<0){
        perror("Connection Failed");
        exit(EXIT_FAILURE);
    }
    if (atoi(returnCode)==100)
    {
        printf("RESPONSE CODE: %s : Connection success\n",returnCode);
    }
    else
    {
        printf("Connection failed\n");
        exit(EXIT_FAILURE);
    }
    int responseCode=0;
    while (menu!=4)
    {
        printf("\n============================\n");
        printf("    1. Log In\n");
        printf("    2. Posting\n");
        printf("    3. Log out\n");
        printf("    4. Exit\n");
        printf("Your choice: ");
        scanf("%d",&menu);
        printf("\n============================\n");
        switch (menu)
        {
            case 1:
                char username[MAX_INPUT_SIZE];
                printf("Enter username: ");
                scanf("%s",username);
                snprintf(buffer, sizeof(buffer)-6, "USER %s", username);
                send(sock, buffer, strlen(buffer), 0);
                printf("REQUEST: '%s'\n", buffer);
                recv(sock, buffer, sizeof(buffer), 0);
                responseCode=atoi(buffer);
                break;

            case 2:
                printf("Enter your post: ");
                char post[MAX_INPUT_SIZE];
                fflush(stdin);
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                fgets(post, sizeof(post), stdin);

                // remove new line (\n) character
                size_t length = strlen(post);
                if (length > 0 && post[length - 1] == '\n') {
                    post[length - 1] = '\0';
                }
                snprintf(buffer, sizeof(buffer)-6, "POST %s", post);
                send(sock, buffer, strlen(buffer), 0);
                printf("REQUEST: '%s'\n", buffer);
                recv(sock, buffer, sizeof(buffer), 0);
                responseCode=atoi(buffer);
                break;
            case 3:
                snprintf(buffer, sizeof(buffer), "BYE");
                send(sock, buffer, strlen(buffer), 0);
                printf("REQUEST: '%s'\n", buffer);
                recv(sock, buffer, sizeof(buffer), 0);
                responseCode=atoi(buffer);
                break;
            default:
                break;
        }
        outputResponse(responseCode);

    }
    printf("\nBye\n\n");
    // send(sock, hello, strlen(hello), 0);
    // printf("Hello message sent\n");
    // valread = read(sock, buffer, sizeof(buffer));
    // printf("%s\n", buffer);

    return 0;
}