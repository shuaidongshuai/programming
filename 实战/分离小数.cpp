#include<stdio.h>
#include<math.h>
int main()
{
	double a,f,i;
	scanf("%lf",&a);
	f=modf(a,&i);		//i和f必须是double型，a可以是float 型 
	printf("%f=%f+%f",a,i,f);
 } 
