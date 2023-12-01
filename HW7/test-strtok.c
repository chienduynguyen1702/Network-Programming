#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char str[80] = "USER admin\r\nPOST Hello world\r\nPOST Test stream\r\n";
    const char s[3] = "\r\n";
    char *token;
    
    /* lay token dau tien */
    token = strtok(str, s);
        printf( "token after strtok : '%s'\n", token );
    
    /* duyet qua cac token con lai */
    while( token != NULL ) 
    {
            char * token_copy = strdup(token);
            // printf( "token_copy: '%s'\n", token_copy );
            free(token_copy);
            token = strtok(NULL, s);
            printf( "token after strtok : '%s'\n", token );
    }
    
   return(0);
}