#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int main()
{
	double x=4.5,y,z;
	y=modf(x,&z);
	printf("%.2f=%.2f+%.2f",x,z,y);
 } 
