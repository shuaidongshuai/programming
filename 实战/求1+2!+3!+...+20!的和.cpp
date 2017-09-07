#include<stdio.h>
int main()
{
	int i,j=1,sum;
	for(i=1;i<=20;i++)
	{
		j*=i;
		sum+=j;
	}
	printf("%d",sum);
 } 
