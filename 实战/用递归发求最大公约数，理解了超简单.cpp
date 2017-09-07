#include<stdio.h>
int dong(int a,int b)
{
	return b?dong(b,a%b):a;		//不用管a与b谁大，因为就算b大,递归一次就把ab的位子换了 
}
int main()
{
	int a,b;
	printf("请输入两个数(用逗号隔开)：");
	scanf("%d,%d",&a,&b); 
	int x=dong(a,b);
	printf("最大公约数是：%d",x);
 } 
