#include<stdio.h>
int dong(int n)
{
	if(n==1)
	{
		return 1;
	}
	else
	{
		return n*dong(n-1);
	}
}
int main()
{
	int a,b;
	printf(" ‰»Î£∫");
	scanf("%d",&b);
	a=dong(b);
	printf("%d",a);
 } 
