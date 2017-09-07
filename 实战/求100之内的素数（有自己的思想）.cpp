#include<stdio.h>
#include<math.h>
#define N 101
int main()
{
	int a[N],i,j;
	for(i=2;i<N;i++)
	{
		a[i]=i;
	}
	for(i=2;i<N;i++)
	{
		for(j=2;j<=sqrt(i);j++)
		{
			if(i%j==0)
			{
			a[i]=0;
			break;
		}
		}
	}
	for(i=2;i<N;i++)
	{
		if(a[i]!=0)
		printf("%d\t",a[i]); 
	}
}
