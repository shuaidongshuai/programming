#include<stdio.h>
int dong(int a,int b)
{
		b=a;
	a=a+b;
	return b;
}
int main()
{
	int a=1,b=3,c;
	c=dong(a,b);
	printf("%d,%d,%d",a,b,c);
}
