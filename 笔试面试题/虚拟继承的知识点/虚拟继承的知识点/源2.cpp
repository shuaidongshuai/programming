#include <iostream>
using namespace std;
class a
{
	virtual void func();
	char x;
};
class b :public virtual a
{
	virtual void foo();
};

void test3()
{
	cout << sizeof(a) << endl;
	cout << sizeof(b) << endl;
	cout << "-------------------------------------" << endl;
}

/*
8
16
*/