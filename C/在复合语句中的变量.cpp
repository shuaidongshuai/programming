#include<stdio.h>
int main()
{
	int i=1,j=2;
	{
		int s=2;
		j=i+s;
		printf("j=%d\n",j);
		printf("i=%d\n",i);
	}
	printf("j=%d",j);
 } 
