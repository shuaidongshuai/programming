#include<stdio.h>
int f(int n)
{
	if(n<10)
	printf("%d",n);
	else
	{
		printf("%d",n%10);
		f(n/10); 
	}
}
int main()
{
	int x;
	scanf("%d",&x);
	f(x);
}
