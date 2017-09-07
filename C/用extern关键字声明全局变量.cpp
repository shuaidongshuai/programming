#include<stdio.h>
int funct(int x,int y)
{
	int z;
	z=3*x+y;
	return z;
}
int main()
{
	extern int  A,B; 
	printf("the result is %d",funct(A,B));
}
int A=3,B=5;
