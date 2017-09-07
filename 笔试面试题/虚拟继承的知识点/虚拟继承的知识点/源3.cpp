#include <iostream>
using namespace std;
class a
{
	virtual void func();
	char x;
};
class b :public a
{
	//virtual void foo();
};

void test4()
{
	cout << sizeof(a) << endl;
	cout << sizeof(b) << endl;
	cout << "-------------------------------------" << endl;
}

/*
8
8
*/