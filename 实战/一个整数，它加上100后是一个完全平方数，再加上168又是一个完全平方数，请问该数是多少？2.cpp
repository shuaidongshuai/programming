#include<stdio.h>
#include<math.h>
int main()
{
	long int a,m,n;
	for(a=1;;a++)
	{
	m=sqrt(a+100);
	n=sqrt(a+268);
	if(m*m==a+100&&n*n==a+268)
	{
		printf("\n%ld",a);
		break;
	}
}
 } 
