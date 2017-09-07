#include<stdio.h>
int main()
{
	int a,b,c,d;
	printf("输入一个自然数：");
	scanf("%d",&a);
	while(a!=1)
	{
	if(a%2==0) a=a/2;
	else a=a*3+1;
	printf("%d\n",a); 
 } 
 printf("角谷猜想结果：%-5d",a);
}
