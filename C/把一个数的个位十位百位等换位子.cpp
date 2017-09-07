#include<stdio.h>
int  main()
{	
	int sum=0,g=12345;		
	while(g>0)
	{
		sum=sum*10+g%10;
		g/=10;
	}
	printf("\n%d\n",sum);
}
