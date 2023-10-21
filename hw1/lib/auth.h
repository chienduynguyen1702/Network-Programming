// ################# checkAccountStatus #################
// param 1: inputAccountName: input string from user
// param 2: accountList: list of account
// return:  if account is found, return status of activation of accoutn
//			if account is not found, return NOT_EXIST
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
int checkIsLoggedIn(int *isLoggedIn){
    if (*isLoggedIn == TRUE)
    {
        return TRUE;
    }
    return FALSE;
}