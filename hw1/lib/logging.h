void logging(int action,char *input,int message){
	FILE *fptr;
	fptr = fopen("./data/log_20205059.txt", "a");
	if (fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}
    
    //skip logging when user exit program
    if (action == EXIT)
    {
        exit(0);
    }
    
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	// [dd/mm/yyyy hh:mm:ss] $ Chức năng lựa chọn $ Giá trị người dùng cung cấp $ Mã kết quả 
	fprintf(fptr, "[%2d/%2d/%4d %2d:%2d:%2d] $ %d $ %s $ %s \n", tm.tm_mday, tm.tm_mon + 1,  tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec,action,input,message?"+OK":"-ERR");
	
	fclose(fptr);
}