#include<stdio.h>
long long sum(long long a)
{
	return (1+a)*a/2;
}
int main()
{
	long long a,b;
	scanf("%I64d",&a);
	if(a%2==0)
	{
		printf("%I64d",sum(a));
	}
	else
	{
		b=sum(a-1);
		printf("%I64d",b+a);
	}
 } 
