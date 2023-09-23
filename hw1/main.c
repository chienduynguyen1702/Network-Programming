#include <stdio.h>
#include "lib.h"
// ####################### declare function ############################

int startMenu();
int getData();

// ####################### MAIN ############################

int main()
{
	// getData();
	startMenu();
	return 0;
}

// ####################### develop function ############################
int getData()
{
	int data;
	printf("Enter a number: ");
	scanf("%d", &data);
	return data;
}
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
		printf("|Your choice (1-4): ");
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