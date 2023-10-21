#include "auth.h"

// ####################### log in function ############################
// param 1: accountList: list of account
// param 2: inputAccountName: input string from user
// return: TRUE if log in successfully, FALSE if fail
int logIn(account accountList[],char *inputAccountName, int *isLoggedIn)
{
	printf("Username: ");scanf("%s", inputAccountName);
	printf("\n");
	if (checkIsLoggedIn(isLoggedIn)==TRUE){
		printf("You have already logged in.\n");
		return FALSE;
	}
	int result = checkAccountStatus(inputAccountName, accountList);
	// account is banned
	if (result == FALSE) 
	{
		printf("Account is banned\n");
		return FALSE;
	}
	// account is not exist
	if (result == NOT_EXIST) 
	{
		printf("Account is not exist\n");
		return FALSE;
	}
	// account is actived,logged in successfully
	else{
		printf("Hello %s\n", inputAccountName);
		*isLoggedIn = TRUE;
		return TRUE;
	}
}
// ####################### Post message function ############################
int postMessage(char *inputMessage, int *isLoggedIn)
{
	char str[20];
	printf("Post message: ");
	// flush input buffer
	fflush(stdin);
	int c;
    while ((c = getchar()) != '\n' && c != EOF);
	// get input

    fgets(str,20,stdin);
	if (checkIsLoggedIn(isLoggedIn)==FALSE){
		printf("You have not logged in.\n");

		return FALSE;
	}
	int inputLength = strlen(str);
	// remove \n at the end of string
	if (str[inputLength - 1] == '\n')
	{
		str[inputLength - 1] = '\0';
	}
	// printf("|%s|\n",str);
	strcpy(inputMessage,str);
	printf("\nSuccessfully posted!\n");
	return TRUE;
}	