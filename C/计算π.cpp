#include<stdio.h> //π/4=1-1/3+1/5-1/7……
int main() 
{
	double a=1.0,b=3.0,c=-1;
	while(b<10000000000)		//运算次数越多   越准确 
	{
		a+=c/b;
		//printf("%.16f\n",a*4);
		c*=(-1);
		b+=2;
	}
	printf("%.16lf",a*4);
}
