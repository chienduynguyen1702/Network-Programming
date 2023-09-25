#include<stdio.h>


void printEachAccount(account singleAccount){
	printf("|  %-13s|%-15s|\n",singleAccount.accountName,(singleAccount.isActived==TRUE)?"  True":"  False");
}
void printToCheckFile(account accountList[],int lengthOfList){
	printf("---------------------------------\n");
	printf("|%-15s|%-15s|\n","    account  ","  is banned ?");
	printf("---------------------------------\n");
	for ( int i = 0; i < lengthOfList; i++)
	{
		printEachAccount(accountList[i]);
	}
	printf("---------------------------------\n");
}
int getData(char *filePath,account accountList[])
{
	// Open a file in read mode
	FILE *fptr = fopen(filePath, "r");

	// Print some text if the file does not exist
	if(fptr == NULL) {
		printf("Not able to open the file.");
		return FALSE;
	}
	
	//start read data
	// account accountList[NUMBER_OF_LIST];
	int i = 0;
	int readBoolenIsActived;
	while (fscanf (fptr, "%s %d", accountList[i].accountName, &accountList[i].isActived) != EOF) {
		i++;
    }
	// printf("Succesfully get %d account\n",i);
	
	//print to check data
	// int lengthOfList =i;
	// printToCheckFile(accountList,lengthOfList);
	
	// Close the file
	fclose(fptr);
	
	return TRUE;
}