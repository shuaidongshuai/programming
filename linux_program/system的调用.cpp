#include<stdlib.h>
#include<stdio.h>
int main()
{
	int status;
	if((status=system("date"))<0)
	{
		printf("system error\n");
		exit(0);
	}
	printf("exit status =%d\n",status);
	status=system("who");
	printf("exit status=%d\n",status);
	exit(0);
 } 
