//函数默认参数，遇上，函数重载
#include<stdio.h>
int func(int a,int b,int c) 
{
	return a+b+c; 
}
int func(int a,int b)
{
	printf("默认把 字符 ‘A’转化为 整数 65 \n"); 
	return a+b;
}
char func(int a,char b,int c,int d)
{
	printf("默认把  整数 49 转化为 字符 ‘1’ \n");
	return b;
}
int main()
{
	int a;
	
	a = func('A',0);//默认把 字符 ‘A’转化为 整数 65 
	printf("%d\n",a);
	
	
	int  b = func(0,49,0,0);//默认把  整数 49 转化为 字符 ‘1’ 
	printf("%c\n",b);
 }
 
