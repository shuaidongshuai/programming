#include<iostream>
using namespace std;
int main()
{
	const int &b = 1;		//常量的引用 
	cout<<"b = "<<b<<endl;
	
	//b = 2;不能改变b的值
	//用地址
	int *p = (int *)&b;
	*p = 2;					// 敢想 么 竟然把 常量（1） 改为 了 2   说明 b 引用的并不是常量 1的值 
	 
	cout<<"b = "<<b<<endl;
	
	//下面不用 引用，，a == 常量（1） 
	const int a = 1;
	int *q = (int *)&a;
	*q = 2;	 					//就算取地址也不能改变   常量（1）   的值 
	cout<<"a = "<<a<<endl;
	
}
