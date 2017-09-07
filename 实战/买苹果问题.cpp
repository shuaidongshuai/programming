#include<stdio.h>
int main()
{
	float average,a=2,b=0,c=0;
	while(a<=100)
	{
		b=b+0.8*a;
		a*=2;
		c++;
	}
	average=b/c;
	printf("½á¹ûÊÇ£º%f",average);
 } 
