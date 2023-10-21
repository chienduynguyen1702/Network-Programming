// ######################## Logging after each action ########################
// param 1: action: action code
// param 2: input: input string from user
// param 3: message: status code of action
// return: TRUE if success, FALSE if fail
#include <time.h>
// print responses to check
int printResponses(char *responses[])
{
	for (int i = 0; responses[i] != NULL; i++)
	{
		printf("printResponses   %s\n", responses[i]);
	}
	return 0;
}

// copy responses from IP resolver to responses array
// param 1: responses: pointer to array of responses
// param 2: hp: struct hostent *hp
int copyResponsesFromIPResolver(char *responses[], struct hostent *hp)
{
	int i = 0;
	responses[0] = hp->h_name; // Make a copy of the first string
	for (i = 0; hp->h_aliases[i] != NULL; i++)
	{
		responses[i+1] = hp->h_aliases[i]; // Make a copy of the string
	}
	responses[i+1] = NULL; // Terminate the new array with NULL
	return 0;
}

// copy responses from domain resolver to responses array
// param 1: responses: pointer to array of responses
// param 2: addr_list: struct in_addr **addr_list
int copyResponseFromDomainResolver(char *responses[], struct in_addr **addr_list)
{
	int i = 0;
	for (i = 0; addr_list[i] != NULL; i++)
	{
		responses[i] = strdup(inet_ntoa(*addr_list[i])); // Make a copy of the string
	}
	responses[i] = NULL; // Terminate the new array with NULL
	return 0;
}

int logger(char *input, int result, char *responses[])
{
	// skip logging when user exit program, chosing action 4
	FILE *fptr;
	fptr = fopen("./data/log_20205059.txt", "a");
	if (fptr == NULL)
	{
		printf("Can't open log file!");
		return FALSE;
		// exit(1);
	}
	char input_str[20];
	strcpy(input_str, input);

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	// [dd/mm/yyyy hh:mm:ss] $ input $ symbol_result responses
	fprintf(fptr, "[%2d/%2d/%4d %2d:%2d:%2d] $ %s $ %s ", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec, input_str, result ? "+" : "-");

	if (result == NOT_FOUND)
	{
		fprintf(fptr, "Not found information");
	}
	if (responses != NULL)
	{
		for (int i = 0; responses[i] != NULL; i++)
		{
			fprintf(fptr, "%s ", responses[i]);
		}
	}

	fprintf(fptr, "\n");
	fclose(fptr);
	return TRUE;
}