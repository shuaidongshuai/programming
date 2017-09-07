#include<iostream>
#include<tuple>
using namespace std;


void main()
{
	//多元数组
	tuple<char, short, int, double, char*> mytuple('A', 12, 34, 324.423, "hello_world");

	auto a1 = get<0>(mytuple);
	cout << a1 << endl;

	auto a2 = get<1>(mytuple);
	cout << a2 << endl;

	auto a3 = get<2>(mytuple);
	cout << a3 << endl;

	auto a4 = get<3>(mytuple);
	cout << a4 << endl;

	auto a5 = get<4>(mytuple);
	cout << a5 << endl;

	cin.get();
}