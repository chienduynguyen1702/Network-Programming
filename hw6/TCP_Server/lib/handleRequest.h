#include <stdio.h>
#include <string.h>

#define LOG_IN 1
#define POST_MESSAGE 2
#define LOG_OUT 3
#define EXIT 4
#define MAX_INPUT_LENGTH 256
#define ERROR 10

#define TRUE 1
#define FALSE 0
#define NOT_EXIST -1

#define ACTIVED 1
#define BANNED 0

int determineMenuChoice(char *input, char *requestString)
{
    char command[10];
    if (sscanf(input, "%s", command) == 1)
    {
        // Kiểm tra loại request
        if (strcmp(command, "USER") == 0)
        {
            char username[256];
            if (sscanf(input, "%*s %255[^\n]", username) == 1)
            {
                // printf("Command: USER\nUsername: %s\n", username);
                strcpy(requestString, username);
                return LOG_IN;
            }
            else
            {
                // printf("Invalid USER request format.\n");
            }
        }
        else if (strcmp(command, "POST") == 0)
        {
            char postContent[256];
            if (sscanf(input, "%*s %255[^\n]", postContent) == 1)
            {
                // printf("Command: POST\nPost Content: %s\n", postContent);
                strcpy(requestString, postContent);
                return POST_MESSAGE;
            }
            else
            {
                // printf("Invalid POST request format.\n");
                return ERROR;
            }
        }
        else if (strcmp(command, "BYE") == 0)
        {
            // printf("Command: BYE\n");
            return LOG_OUT;
        }
        else
        {
            // printf("Unknown command.\n");
            return ERROR;
        }
    }
    else
    {
        printf("Invalid input format.\n");
        return ERROR;
    }
    return ERROR;
}

int logIn(char *username, account accountList[], int numberOfAccountList, int sessionOnline)
{
    if (sessionOnline)
    {
        return 214; // account has been login on this client
    }
    if (strcmp(username, "") == 0)
    {
        return 300; // invalid request
    }
    
    else
    {
        for (int i = 0; i < numberOfAccountList; i++)
        {
            if (strcmp(username, accountList[i].accountName) == 0)
            {
                if (accountList[i].isOnline == TRUE)
                {
                    return 213; // account has been login on another client
                }

                if (accountList[i].isActived == ACTIVED)
                {
                    accountList[i].isOnline = TRUE;
                    return 110; // login success
                }
                if (accountList[i].isActived == BANNED)
                {
                    return 211; // account has been banned
                }
            }
        }
        return 212; // account does not exist
    }
}

int postMessage(char *postContent, account accountList[], int numberOfAccountList)
{
    printf("Content: '%s' has being posting ...\n ", postContent);
    return 120; // post success
}

int logOut(char *username, account accountList[], int numberOfAccountList)
{
    for (int i = 0; i < numberOfAccountList; i++)
    {
        if (strcmp(username, accountList[i].accountName) == 0)
        {
            accountList[i].isOnline = FALSE;
            return 130; // logout success
        }
    }
    return 212; // account does not exist
}