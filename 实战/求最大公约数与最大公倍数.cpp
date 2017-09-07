#include<stdio.h>
int main()
{
	int a,b,c,d,e;
	scanf("%d%d",&a,&b);		//完全不需要判断a,b的大小 
	e=a; 
	d=b;
	while(e!=0)				//辗转相除法 
	{
		c=d%e;
		d=e;
		e=c;
}
printf("最大公约数：%d\n最小公倍数:%d",d,a*b/d);
 } 
