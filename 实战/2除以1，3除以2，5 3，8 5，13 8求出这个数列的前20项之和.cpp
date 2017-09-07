#include<stdio.h>
int main()
{
	int i;
	float t,sum,a=2,b=1;
	for(i=0;i<20;i++)
	{
		sum+=a/b;
		t=b;
		b=a;
		a=a+t;
	}
	printf("%f",sum);
 } 
