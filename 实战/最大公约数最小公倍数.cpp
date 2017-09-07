#include<stdio.h>
int main()
{
	int t,a,b,c,d;
	printf("请输入连个数a b\n");
	scanf("%d%d",&a,&b);
	c=a,d=b;
	while(b!=0)
	{
		t=b;
		b=a%b;
		a=t;
	}
	printf("多大公约数：%d\n最大公倍数：%d",a,c*d/a);
 } 
