#include<iostream>
using namespace std;

//C++用using取代typedef
using DB = double;//c++风格别名
using array = int[10];
typedef void(*PFD)(double);            // 傳統語法
using PFD = void(*)(double);           // 新增語法

namespace dong
{
	template<class T> 
	T add(T a, T b)
	{
		using t = T;//给模板取别名
		t c = a + b;
		return c;
	}

};

void main()
{
	cout << dong::add(1, 2) << endl;

	cin.get();
}

void main1()
{
	cout << sizeof(DB) << endl;
	cout << sizeof(array) << endl;

	cin.get();
}