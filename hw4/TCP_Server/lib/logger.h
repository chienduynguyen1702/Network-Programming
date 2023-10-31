// ######################## Logging after each action ########################
// param 1: action: action code
// param 2: input: input string from user
// param 3: message: status code of action
// return: TRUE if success, FALSE if fail
#include <time.h>
#include <string.h>
#include <stdio.h>


#define NOT_FOUND 0
#define FOUND 1
#define FALSE 0
#define TRUE 1


// print responses to check
int printResponses(char *responses[])
{
	for (int i = 0; responses[i] != NULL; i++)
	{
		printf("printResponses   %s\n", responses[i]);
	}
	return 0;
}


int logger_connect(char *input,const char *addr,int socket)
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
	char addr_str[20];
	strcpy(addr_str, addr);

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	// [dd/mm/yyyy hh:mm:ss] $ input $ symbol_result responses
	fprintf(fptr, "[%2d/%2d/%4d %2d:%2d:%2d] $ %s:%d $ %s ", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec, addr_str, socket, input_str);

	fprintf(fptr, "\n");
	fclose(fptr);
	return TRUE;
}
int logger_file_tranfer(char *input,const char *addr,int socket, int result, char *responses[])
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
	char addr_str[20];
	strcpy(addr_str, addr);

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	// [dd/mm/yyyy hh:mm:ss] $ input $ symbol_result responses
	fprintf(fptr, "[%2d/%2d/%4d %2d:%2d:%2d] $ %s:%d $ %s $ %s", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec, addr_str, socket, input_str, result?"+OK Successful upload":"-ERR FAIL");

	fprintf(fptr, "\n");
	fclose(fptr);
	return TRUE;
}