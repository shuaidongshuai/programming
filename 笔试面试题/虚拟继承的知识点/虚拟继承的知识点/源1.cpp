#include <iostream>
using namespace std;
class a
{
	virtual void func();
};
class b :public a
{
	virtual void foo();
};
class c :public a
{
};

void test2()
{
	cout << sizeof(a) << endl;
	cout << sizeof(b) << endl;
	cout << sizeof(c) << endl;
	cout << "-------------------------------------" << endl;
}

/*
4
4
4				---- 可以看出，基类和派生类公用一个vptr指针
*/