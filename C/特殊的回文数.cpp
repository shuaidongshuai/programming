#include<stdio.h>
int main()
{
	int a,b,c,n;
	scanf("%d",&n);
	for(a=1;a<10;a++)
	{
		for(b=0;b<10;b++)
		{
			if(a+b<54)
			for(c=0;c<10;c++)
			{
				if(a+b+c+b+a==n)
				printf("%d%d%d%d%d\n",a,b,c,b,a);
			}
		}
	
	}
	for(a=1;a<10;a++)
	{
		for(b=0;b<10;b++)
		{
			if(a+b<54)
			for(c=0;c<10;c++)
			{
				if(a+b+c+c+b+a==n)
				printf("%d%d%d%d%d%d\n",a,b,c,c,b,a);
			}
		}
	
	}	
	return 0;
 } 
