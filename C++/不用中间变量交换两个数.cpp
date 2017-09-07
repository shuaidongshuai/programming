#include<stdio.h>
int swap(int &a,int &b)
{
	a += b;
	b = a - b;
	a = a - b;
}
int main()
{
	int a = 1;
	int b = 2;
	printf("a = %d\nb = %d\n",a,b);
	swap(a,b);
	printf("a = %d\nb = %d",a,b);
 } 
