#include <stdio.h> 
#include <math.h>
int main()
{
	float a,b,c,l,h1,s;
	printf("请输入能组成三角形的三条边每个数字用，隔开：\n");
	scanf("%f,%f,%f",&a,&b,&c);
	printf("%f,%f,%f",a,b,c);
	l=a+b+c;
	h1=l/2;
	s=sqrt(h1*(h1-a)*(h1-b)*(h1-c));
	printf("三角形的周长和面积分别为： \n");
	printf("l=%4.2f,s=%4.2f",l,s);
 } 
