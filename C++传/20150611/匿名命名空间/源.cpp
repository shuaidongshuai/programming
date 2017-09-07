#include<iostream>
//using namespace std;
//匿名命名空间
namespace
{
	int num = 100;
}
//int num = -100;  //不能加这句话了 。。。 匿名命名空间里面的变量就相当于全局变量了 。。 会发生冲突

namespace dong = std;//给std起别名（不推荐）
void main()
{
	num = -2;
	dong::cout << num << dong::endl;

	std::cin.get();
}