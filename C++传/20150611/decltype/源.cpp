#include<iostream>
using namespace std;

void main()
{
	auto i = 10;
	cout << typeid(i).name() << endl;

	auto i2{ 1, 2, 3, 4 };
	cout << typeid(i2).name() << endl;

	//根据一个变量，获取他的类型，来创建一个数组
	decltype(i) dong[6]{1, 2, 3, 4, 5, 6};

	for (auto i : dong)
	{
		cout << i << endl;
	}

	cin.get();
}