
// ####################### log in function ############################
int checkAccountStatus(char *inputAccountName, account accountList[]){
	for (int i = 0; i < NUMBER_OF_LIST; i++)
	{
		if (strcmp(inputAccountName, accountList[i].accountName) == 0)
		{
			return accountList[i].isActived;
		}
	}
	return NOT_EXIST;
}

int logIn(account accountList[],char *inputAccountName)
{
	printf("Username: ");scanf("%s", inputAccountName);
	printf("\n");
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
		return TRUE;
	}
}
// ####################### Post message function ############################
int postMessage(char *input)
{
	char str[20];
	printf("Post message: ");
	// flush input buffer
	int c;
    while ((c = getchar()) != '\n' && c != EOF);
	// fflush(stdin);
	// get input
    fgets(str,20,stdin);
	int inputLength = strlen(str);
	// remove \n at the end of string
	if (str[inputLength - 1] == '\n')
	{
		str[inputLength - 1] = '\0';
	}
	// printf("|%s|\n",str);
	strcpy(input,str);
	printf("\n");
	return TRUE;
}	