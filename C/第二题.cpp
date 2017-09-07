#include<stdio.h>
int main()
{
	 int i,n=1;
	 for(i=0;i<20;i++)
	 n*=2;
	 float sum=1;
	for(i=1;i<=30;i++)
	{
		sum*=2;
		if(sum==n)
		{
			printf("%d  ",i);
			break;
			}
		if(sum>n)
		continue;
	}
}
