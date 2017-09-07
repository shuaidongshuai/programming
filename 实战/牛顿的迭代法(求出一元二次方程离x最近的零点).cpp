#include<stdio.h>
#include<math.h>
float dong(float a,float b,float c)
{
	float x=3,x0,f,f1;			//x不能等于0 
	while(fabs(x-x0)>=1e-5)
	{
		x0=x;
		f=(a*x0+b)*x+c;
		f1=2*a*x0+b;
		x=x0-f/f1;
	}
	return x;
 } 
 int main()
 {
 	float a,b,c;
 	scanf("%f%f%f",&a,&b,&c);
 	printf("%f",dong(a,b,c));
  } 
