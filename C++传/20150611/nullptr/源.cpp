#include<iostream>
using namespace std;

void test(int i)
{
	cout << typeid(i).name() << endl;
}
void test(int *i)
{
	cout << typeid(i).name() << endl;
}

void main()
{
	test(NULL);//在c++中  NULL  代表整数 0 
	test(nullptr);//在c++中  nullptr  代表 空指针

	cout << typeid(NULL).name() << endl;
	cout << typeid(nullptr).name() << endl;
	//C++严格类型匹配

	cin.get();
}