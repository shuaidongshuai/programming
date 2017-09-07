#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main() 
{
	int i,j;
	srand(time(NULL));
	for(j=0;j<10;j++)
	{
		for(i=0;i<10;i++)
		{
		printf("%d\t",rand()%100+1);
	}
	printf("\n");
	}
}
