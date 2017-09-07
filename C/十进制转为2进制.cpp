#include<stdio.h>
int dong(int a)
{
	int b=a%2;
	if(a!=0)
	dong(a/2);
	printf("%d",b);
}
int main()
{
	dong(10);
 } 
