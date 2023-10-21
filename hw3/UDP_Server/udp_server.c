#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h> // Added for gethostbyaddr
#include <time.h>
// ####################### define ########################
#define BUFF_SIZE 2048
#define DOMAIN_INPUT 0
#define IP_INPUT 1
#define NOT_FOUND 0
#define FOUND 1
#define FALSE 0
#define TRUE 1

// ####################### import internal lib ######################
#include "./lib/resolveDNS.h"
#include "./lib/logger.h"

// ####################### MAIN ############################
int main(int argc, char **argv)
{

    if (argc != 2)
    {
        printf("usage: %s <server_port>\n", argv[0]);
        return 0;
    }

    int server_port = atoi(argv[1]);
    int server_sock;
    char buff[BUFF_SIZE];

    struct sockaddr_in server_addr, client_addr;
    int bytes_received, sin_size;

    int input_type = 0;  // 0: domain name, 1: ip address
    int result = 0;      // 0: not found, 1: found
    char *responses[10]; // store responses from server
    int check = 1;

    // Construct a UDP socket
    if ((server_sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("\nError: ");
        return 0;
    }

    // Bind the socket
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) < 0)
    {
        perror("\nError: ");
        return 0;
    }

    sin_size = sizeof(struct sockaddr);
    // Communicate with client
    while (1)
    {
        // Receive data from client
        bytes_received = recvfrom(server_sock, buff, BUFF_SIZE - 1, 0, (struct sockaddr *)&client_addr, &sin_size);
        if (bytes_received < 0)
        {
            perror("Error: ");
            close(server_sock);
            return 0;
        }
        buff[bytes_received] = '\0';
        struct in_addr ip;

        // Print out the received request
        printf("Received request: %s\n", buff);

        // if input param is ipv4
        if (inet_pton(AF_INET, buff, &ip) == 1)
        {
            input_type = IP_INPUT;
            struct hostent *hp;
            hp = ipToDomain(ip);

            // if ip is not valid
            if (hp == NULL)
            {
                result = NOT_FOUND;
                responses[0] = NULL;
            }

            // if ip is valid
            else
            {
                result = FOUND;

                printf("Result: %s ", hp->h_name);
                copyResponsesFromIPResolver(responses, hp);
                for (int i = 0; hp->h_aliases[i] != NULL; i++)
                {
                    printf("%s ", hp->h_aliases[i]);
                }
                printf("\n");
            }
        }

        // if input param is domain name
        else
        {
            input_type = DOMAIN_INPUT;
            struct in_addr **addr_list;
            addr_list = domainToIp(buff);

            // if domain name is not valid
            if (addr_list == NULL)
            {
                result = NOT_FOUND;
                responses[0] = NULL;
            }
            // if domain name is valid
            else
            {
                result = FOUND;
                printf("Result: ");
                copyResponseFromDomainResolver(responses, addr_list);
                for (int i = 0; responses[i] != NULL; ++i)
                {
                    printf(" %s ", responses[i]);
                }
                printf("\n");
            }
        }

        // printResponses(responses);
        logger(buff, result, responses);
    }

    close(server_sock);
    free(responses);
    return 0;
}
