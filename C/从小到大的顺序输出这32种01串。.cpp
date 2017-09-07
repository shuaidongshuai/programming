#include<stdio.h>
int x=5;
void dong(int a)
{
	x--;
	int b=a%2;
	a/=2;
	if(a!=0)
	dong(a);
	if(a==0)
	{
		for(x;x>0;x--)
		printf("0");
	}
	printf("%d",b);
}
int main()
{
	int i,n=0;
	for(n=0;n<=31;n++)
	{
		dong(n);
		printf("\n");
		x=5;
	}
}
