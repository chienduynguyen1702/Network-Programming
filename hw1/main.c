#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

// ####################### define ########################
#define TRUE 1
#define FALSE 0 
#define NOT_EXIST -1
#define NUMBER_OF_LIST 30

// ####################### define menu choice ########################
#define LOG_IN 1
#define POST_MESSAGE 2
#define LOG_OUT 3
#define EXIT 4
// ####################### account - activationValue struct ########################
typedef struct ACCOUNT
{
	char accountName[20];
	int isActived;
} account;

// ####################### import lib ######################
#include "./lib/importData.h"
#include "./lib/logger.h"
#include "./lib/menu.h"
// ####################### declare function ############################

int startMenu(account accountList[]);

// ####################### MAIN ############################

int main()
{
	// Get data from file
	account accountList[NUMBER_OF_LIST];
	int result = getData("./data/account.txt",accountList);
	if (result != TRUE) {
        // Handle the error here, if needed
		printf("Error when get data from file\n");
        return result;
    }

	// Start menu
	startMenu(accountList);

	return 0;
}

// ##################################################################
// ####################### menu function ############################
// ##################################################################
// param : accountList: array of account as a struct

int startMenu(account accountList[])
{
	int choice;
	int isLoggedIn = FALSE;
	char input[20]="";
	
	// return status code after each choice in menu
	int statusCode;
	
	do
	{
		printf("--------------------\n");
		printf("|1. Log in         |\n");
		printf("|2. Post message   |\n");
		printf("|3. Log out        |\n");
		printf("|4. Exit           |\n");
		printf("--------------------\n");
		printf("=> Your choice (1-4): ");
		scanf("%d", &choice);
		printf("\n");
		switch (choice)
		{
			case 1:
				if (isLoggedIn == TRUE) {
					printf("You have already logged in.\n");
					break;
				}
				statusCode = logIn(accountList,input);
				// set isLoggedIn = TRUE if log in successfully
				if (statusCode == TRUE) {
					isLoggedIn = TRUE;
				}
				break;

			case 2:
				statusCode = postMessage(input);

				// check if input account has logged in
				if (isLoggedIn == FALSE) {
					printf("You have not logged in.\n");
					statusCode = FALSE;
					break;
				}
				else {
					printf("Successfully posted!\n");
					
				}
				break;

			case 3:	
				// check if input account has logged in
				if (isLoggedIn == FALSE) {
					printf("You have not logged in.\n");
					statusCode = FALSE;
					break;
				}
				else {
					// set isLoggedIn = FALSE if log out successfully
					isLoggedIn = FALSE;
					printf("Successfully logged out\n");
					strcpy(input,"");
				}
				break;

			case 4:	
				printf("Exit!\n");
				break;
			default:
				printf("Invalid input! Try again\n");
				break;
		}
		printf("\n");
		logger(choice,input,statusCode);
	} while (choice != 4);
	return 0;
}
