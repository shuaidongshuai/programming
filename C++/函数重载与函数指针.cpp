#include<stdio.h>
int func(int a,int b,int c)
{
	return a+b+c; 
}
int func(int a,int b)
{
	return a+b;
}

typedef int( *dong)(int,int);//定义一个 名为dong 返回值为 int  参数为 int ,int  的函数**指针** 

int main()
{
	dong P = func;//自动匹配  int func(int a,int b)
				//匹配时要注意：1、函数参数列表一致	 2、函数返回类型要一样
	int c = P(1,2); 
	printf("%d\n",c);
 }
