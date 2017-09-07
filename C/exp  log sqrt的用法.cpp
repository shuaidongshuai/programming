#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int main()
{
	double x=1;
	double y=2.718280,z=100;
	printf("exp(%f)=%f\n",x,exp(x));					/*计算e的x次方*/ 
	printf("log(%f)=%f\n",y,log(y));					/*以e为底*/ 
	printf("log10(%f)=%f\n",z,log10(z)); 				/*以10为底*/ 
	printf("sqrt(%f)=%f\n",z,sqrt(z));					/*计算100的平方根*/ 
 } 
