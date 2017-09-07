#include<stdio.h>
int main()
{
    int i,a=1,n,b=1;
    printf("想看几个数：");
	scanf("%d",&n); 
	if(n==1) printf("1\n");
	if(n==2) printf("1\n1\n");
	if(n>2)
	{
		printf("1\t1\t");
		for(i=3;i<n+1;i++)
		{
		a=a+b;
		b=a-b;
		printf("%d\t",a);
		if(i%5==0)  printf("\n");
	}
	}
 } 
