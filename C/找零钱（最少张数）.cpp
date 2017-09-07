#include<stdio.h>
int main()
{
	int a[6]={1,5,10,20,50,100},n,sum;
	while(1)
	{
		sum=0;
		scanf("%d",&n);
		int i,j;
		for(i=5;i>=0;)
		{
			if(a[i]<=n)
			{
				n-=a[i];
				sum++;
				continue;
			}
			if(n==0)
			{
				printf("%d\n",sum);
				break;
			}
		
			i--;
		}
	}

 } 
