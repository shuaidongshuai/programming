#include<stdio.h>
int main()
{
	int b=10;
	int c=1,d=2;
	
	int *p;
	p=&c;
	
	unsigned long *q;
	q=(unsigned long *)0x10000;		// 指定地址 为 100000    不过好像指定的地址有范围  应该是有些地址 系统占用了 所以自己没有权限访问  
	*q=123;					// 对地址指向的内容赋值  123 	相当于	(*(int *)100000)=1  一个道理 
	printf("%d\t%d\n%d\t%d\n%d\t%d\n%d\t%d\n%d\t%x\n",b,&b,c,&c,d,&d,*p,p,*q,q);	
 } 
