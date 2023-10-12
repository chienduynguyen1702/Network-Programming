#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
// function domainToIp: convert domain name to ip
// param : param - input domain name
// return: 0 if success, 1 if fail
int domainToIp(char *param) {
    struct hostent *he;
    struct in_addr **addr_list;

    // check if input domain is valid
    if ((he = gethostbyname(param)) == NULL) {
        herror ("Not found information");
        return 1;
    }

    addr_list = (struct in_addr **) he->h_addr_list;

    printf("Result: \n");
    for(int i = 0; addr_list[i] != NULL; ++i) {
        printf("%s\n", inet_ntoa(*addr_list[i]));
    } 
    return 0;
}
// function ipToDomain: convert ip to domain name
// param : ip - input ip
// return: 0 if success, 1 if fail
int ipToDomain(struct in_addr ip) {
    struct hostent *hp;

    // check if input IP is valid
    if ((hp = gethostbyaddr((const void *)&ip, sizeof ip, AF_INET)) == NULL) {
        herror("Not found infomation");
        return 1;
    }

    printf("Result: \n");
    printf("%s\n", hp->h_name);
    for (int i = 0; hp-> h_aliases[i] != NULL; i++) {
        printf("%s\n", hp->h_aliases[i]);
    }

    return 0;
}

struct in_addr ip;

int main(int argc, char *argv[]) {
    // check if input param is valid
    if (argc != 2) {
        printf("Wrong parameter \n");
        printf("Please try again: \n");
        printf("./resolver <ipv4> \n");
        printf("./resolver <domain_name> \n");
        return 1;
    }

    // check if input param is ipv4 or domain name
    if (inet_pton(AF_INET, argv[1], &ip) == 1) {    // if input param is ipv4
        return ipToDomain(ip);
    } else {                                        // if input param is domain name
        return domainToIp(argv[1]);
    }
    
    
    return 0;
}