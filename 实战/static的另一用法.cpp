#include<stdio.h>
int main()
{
	int sum=0,i;
	for(i=0;i<3;i++)
	{
		printf("a %d ",sum);
		sum++;
		static int sum=10;
		printf("b %d ",sum);
		sum++;
}
 } 
