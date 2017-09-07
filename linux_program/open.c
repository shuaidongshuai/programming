#include<stdio.h>
int main()
{
	if(fopen("dong","r+")<0)
	{
		printf("error\n");
		return 1;
	}
	else
	{
		printf("success");
	}
}