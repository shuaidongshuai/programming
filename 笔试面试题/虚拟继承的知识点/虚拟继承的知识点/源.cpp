#include <iostream>
using namespace std;
class a
{
	virtual void func();
};
class b :public virtual a
{
	virtual void foo();
};

void test1()
{
	cout << sizeof(a) << endl;
	cout << sizeof(b) << endl;
	cout << "-------------------------------------" << endl;
}
/*
4
12              ---------   a中继承了一个vptr(4B) 虚继承一个vptr(4B) b类自己指向虚函数表的指针(4B)  == 12 B
*/