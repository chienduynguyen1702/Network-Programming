#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define MAX_CLIENTS 10
#define MAX_BUFFER_SIZE 1024

#define LOG_IN 1
#define POST_MESSAGE 2
#define LOG_OUT 3
#define EXIT 4


#define TRUE 1
#define FALSE 0 
#define NOT_EXIST -1
#define NUMBER_OF_LIST 30
typedef struct ACCOUNT
{
	char accountName[20];
	int isActived;
	int isOnline;
	
} account;

account accountListGlobal[NUMBER_OF_LIST];

#include "./lib/importData.h"
#include "./lib/handleRequest.h"
#include "./lib/response.h"


void *handle_client(void *socket_desc) {
    int handleRequestResult = 0;
    int sessionOnline = FALSE;
    int client_socket = *(int *)socket_desc;
    char buffer[MAX_BUFFER_SIZE] = {0};
    char requestString[MAX_BUFFER_SIZE] = {0};
    int menu=-1;
    int valread;
    char successConnectedCode[3] = "100";
    char currentUserName[20] = {0};
    printf("Client connected at session %d.\n",client_socket);
    write (client_socket, successConnectedCode, sizeof(successConnectedCode));
    // char cwd[1024]; // current working directory
    // if (getcwd(cwd, sizeof(cwd)) != NULL) {
    //     printf("Current working directory: %s\n", cwd);
    // } else {
    //     perror("getcwd() error");
    //     return 1;
    // }
    // printToCheckFile(accountList,NUMBER_OF_LIST);
    while ((valread = read(client_socket, buffer, sizeof(buffer))) > 0) {
        // remove endline character
        buffer[strcspn(buffer, "\n")] = 0;
        printf("buffer: '%s'\n", buffer);

        menu = determineMenuChoice(buffer, requestString);
        // printf("Client message: '%d' '%s'\n",menu ,requestString);
        // printf("buffer: '%s'\n", buffer);
        // printf("requestString: '%s'\n", requestString);
        // if (strcmp(requestString, "") == 0) {
        //     handleRequestResult=300;
        //     continue;
        // }
        // printf("menu: %d\n", menu);
        switch (menu)
        {
        case LOG_IN:
            printf("Command: USER\nUsername: %s\n", requestString);
            printToCheckFile(accountListGlobal,6);
            handleRequestResult = logIn(requestString, accountListGlobal,NUMBER_OF_LIST,sessionOnline);
            printf("handleRequestResult: %d\n", handleRequestResult);
            printToCheckFile(accountListGlobal,6);
            sessionOnline = (handleRequestResult == 110) ? TRUE : sessionOnline;
            if (sessionOnline) {
                strcpy(currentUserName, requestString);
            }            
            break;
        case POST_MESSAGE:
            // printf("Command: POST\nPost content: %s\n", requestString);
            if (sessionOnline == FALSE) {
                handleRequestResult = 221;
            } else {
                handleRequestResult = postMessage(requestString, accountListGlobal,NUMBER_OF_LIST);
            }
            break;
        case LOG_OUT:
            // printf("Command: BYE\n");
            if (sessionOnline == FALSE) {
                handleRequestResult = 221;
            } else {
                handleRequestResult = logOut(currentUserName, accountListGlobal,NUMBER_OF_LIST);
                if (handleRequestResult == 130) {
                    sessionOnline = FALSE;
                    memset(currentUserName, 0, sizeof(currentUserName));
                }
            }
            break;
        default:
            handleRequestResult = 300;
            // snprintf(buffer, sizeof(buffer), "Invalid request.");
            break;
        }
        outputResponse(handleRequestResult);

        snprintf(buffer, sizeof(buffer), "%d", handleRequestResult);
        // printf("Client message: '%s'\n", buffer);
        write(client_socket, buffer, strlen(buffer));
        memset(buffer, 0, sizeof(buffer));
        memset(requestString, 0, sizeof(requestString));
        printf("\n\n");
    }
    // if (valread == 0) {
    //     printf("Client disconnected\n");
    // } else {
    //     perror("recv failed");
    // }

    close(client_socket);
    printf("Client disconnected at session %d.\n",client_socket);
    free(socket_desc);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <Port_Number>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int server_fd, new_socket, *new_sock;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    // if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
    //     perror("Setsockopt failed");
    //     exit(EXIT_FAILURE);
    // }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(atoi(argv[1]));

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, MAX_CLIENTS) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    printf("Server is running on port %d\n", atoi(argv[1]));


    char * filePath = "./TCP_Server/data/account.txt";
    getData(filePath,accountListGlobal);
    
    
    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        pthread_t sniffer_thread;
        new_sock = malloc(1);
        *new_sock = new_socket;

        if (pthread_create(&sniffer_thread, NULL, handle_client, (void *)new_sock) < 0) {
            perror("Could not create thread");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
