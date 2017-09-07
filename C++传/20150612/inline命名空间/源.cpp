#include<iostream>
using namespace std;

namespace all
{
	namespace V2014
	{
		void fun()
		{
			cout << "V2014" << endl;
		}
	}
}
namespace all
{
	namespace V2015//设置默认版本。原理：inline就相当于在all中直接展开了
	{
		void fun(int a)
		{
			cout << "V2015" << endl;
		}
	}
}


void main()
{
	all::V2014::fun();
	all::V2015::fun(1);
//	all::fun();//默认版本

	cin.get();
}