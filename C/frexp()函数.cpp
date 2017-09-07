#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int main()
{
	float x,y;
	int p;
	printf("输入实数：");
	scanf("%f",&y);
	x=frexp(y,&p);		/*虽然p为一个int型指针，但上面不能写成*p        */ 
	printf("%.2f的尾数是%.2f,指数是%d\n",y,x,p);
	printf("%.2f=%.2f*2^%d\n",y,x,p);
 } 
