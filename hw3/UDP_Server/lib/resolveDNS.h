#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>




struct in_addr ** domainToIp(char *param) {
    struct hostent *he;
    struct in_addr **addr_list;

    // check if input domain is valid
    if ((he = gethostbyname(param)) == NULL) {
        printf("Error: %s is not a valid domain name\n", param);
        return NULL;
    }

    addr_list = (struct in_addr **) he->h_addr_list;
    return addr_list;
}





// function ipToDomain: convert ip to domain name
// param : ip 
// return: 
struct hostent* ipToDomain(struct in_addr ip) {
    struct hostent *hp;

    // check if input IP is valid
    if ((hp = gethostbyaddr((const void *)&ip, sizeof ip, AF_INET)) == NULL) {
        printf("Error: %s is not a valid IP address\n", inet_ntoa(ip));
        return NULL;
    }
    return hp;
}