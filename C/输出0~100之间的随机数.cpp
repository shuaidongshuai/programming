#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{
		int j,i;
	srand(time(0));
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			printf("%d\t",rand()*100/32767);
			}	
			printf("\n");
	}
 } 
