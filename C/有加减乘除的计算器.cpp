#include<stdio.h>
int main()
{
	float a,b,m;
	char op;
	printf("请输入：");
	scanf("%f%c%f",&a,&op,&b);
	switch(op)
	{
		case '+':m=a+b;break;
		case '-':m=a-b;break;
		case '*':m=a*b;break;
		case '/':m=a/b;break;
		default:printf("加减乘除输入都出错，我也是醉了了\n");
 }
 printf("%.2f%c%.2f=%.2f",a,op,b,m);
}
