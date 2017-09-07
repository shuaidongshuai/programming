#include<iostream>
using namespace std;
//int num = 100000;  但是如果有真正的全局变量，访问的就是这个，而不是 num = -100;

namespace n
{
	int num = -100;
}
using namespace n;//使用命名空间，直接当做全局变量来使用

//内层覆盖外层
namespace dong
{
	int num = 100;
	namespace run
	{
		void show()
		{
			int num = 10;
			cout << num << endl;
			cout << dong::num << endl;
			cout << ::num << endl;//  ：：直接访问全局变量
		}
	}
}
using namespace dong;//这句话一定要放到命名空间下面


void main()
{
	run::show();

	cin.get();
}