#include <stdio.h>
#include <stdbool.h>
#define TRUE 0
#define FALSE 1 
#define NUMBER_OF_LIST 30

// ####################### account - key struct ########################
typedef struct ACCOUNT
{
	char accountName[20];
	int isBanned;
} account;

// ####################### import lib ######################
#include "./lib/import_data_lib.h"
#include "./lib/logging.h"

// ####################### declare function ############################

int startMenu();

// ####################### MAIN ############################

int main()
{
	// Get data from file
	int result = getData("account.txt");
	if (result != 0) {
        // Handle the error here, if needed
        return result;
    }

	// Start menu
	startMenu();

	return 0;
}

// ####################### menu function ############################

int startMenu()
{
	int choice;
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
				printf("Log in\n");
				break;
			case 2:
				printf("Post message\n");
				break;
			case 3:	
				printf("Log out\n");
				break;
			case 4:	
				printf("Exit!\n");
				break;
			default:
				printf("Invalid input! Try again\n");
				break;
		}
		printf("\n");
	} while (choice != 4);
}