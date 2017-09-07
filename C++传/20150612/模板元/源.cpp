#include<iostream>
/*
模板元实现递归加速
执行速度快，编译慢。。。把运行时间节约在编译上

当然如果能非递归，最好。。。编译快，执行快
*/


//汉诺塔  递归解决
int hanta1(int n)
{
	if (n == 1)
		return 1;
	else if (n == 2)
		return 2;
	else
		return hanta1(n - 1) + hanta1(n - 2);
}
//非递归
int hanta2(int n)
{
	if (n == 1)
		return 1;
	else if (n == 2)
		return 2;
	else
	{
		int sum = 0;
		int a = 1, b = 2;
		for (int i = 3; i <= n; i++)
		{
			sum = a + b;
			a = b;
			b = sum;
		}
		return sum;
	}
}
//模板元
template<int N>
struct data
{
	//递归
	enum{ res = data<N - 1>::res + data<N - 2>::res };
};
template<>
struct data<1>
{
	enum{ res = 1 };
};
template<>
struct data<2>
{
	enum{ res = 2 };
};
void main()
{
	//std::cout << hanta1(40) << std::endl;
	std::cout << data<70>::res << std::endl;
	std::cout << hanta2(70) << std::endl;

	std::cin.get();
}