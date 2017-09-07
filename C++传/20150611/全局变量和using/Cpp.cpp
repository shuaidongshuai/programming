#include<iostream>

int a = 10;

namespace
{
	//只是相当于全局。但不等于全局。当全局没有a = 10  才相当于全局
	int a = 55;//只要不调用a  就是发生编译出错。因为不调用。这个命名空间就不编译
}
void main()
{
	//std::cout << a << std::endl;//不行  "a" 不明确	

	std::cout << ::a << std::endl;//使用全局的a

	std::cin.get();
}