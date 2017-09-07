#include<stdio.h>
#include<math.h>
int main()
{
	float a,b,c,x1,x2;
	while(1)
	{ 
	scanf("%f%f%f",&a,&b,&c);
	if(a==0)
	{
		printf("x=%.2f\n\n",-1*c/b);
		return 0;
	}
	float t=b*b-4*a*c;
	if(0==t)
	{
		printf("x=%.2f\n\n",-1*b/2/a);
	}
	if(t>0)
	{
		x1=(-1*b+sqrt(t))/2/a;
		x2=(-1*b-sqrt(t))/2/a;
		printf("x1=%.2f\nx2=%.2f\n\n",x1,x2);
	}
	if(t<0)
	{
		float a1,b1;
		a1=-1*b/2/a;
		b1=sqrt(-1*t)/2/a;
		printf("x1=%.2f+%.2fi\nx2=%.2f+%.2fi\n\n",a1,b1,a1,-1*b1);
	}
	} 
	return 0;
 }
