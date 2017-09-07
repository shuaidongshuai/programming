#include<stdio.h>
#include<stdlib.h> 
int main()
{
	int i,j;
	for(j=0;j<10;j++)
	{
		for(i=0;i<10;i++)
		{
			printf("%d\t",rand());
		}
		printf("\n");
	}
 } 
