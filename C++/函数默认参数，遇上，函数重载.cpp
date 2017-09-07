//函数默认参数，遇上，函数重载
#include<stdio.h>
int func(int a,int b,int c =1)//带默认参数的函数 
{
	return a+b+c; 
}
int func(int a,int b)
{
	return a+b;
}
int main()
{
	int a;
	//a = func(1,2);  会报错 [Error] call of overloaded 'func(int, int)' is ambiguous  错误原因：存在二义性 
	
	printf("%d\n",a);
 }
 //一般  函数重载 和 函数默认参数 不要同时写 
