#include<stdio.h>
int main()
{
	int *p;
	p=(int *)95000;
	char *a;
	a = (char *)96000;
	printf("%d  %d\n",p,p+1);//注意指针加 1 不是地址加1     地址 = 类型 * 1  （int 型 就是 4 * 1） 
	printf("%d  %d",a,a+1);													//（char 型 就是 1*1） 
 } 
