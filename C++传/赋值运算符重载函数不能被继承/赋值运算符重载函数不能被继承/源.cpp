#include <iostream>
using namespace std;

class A1
{
public:
	int operator=(int a)
	{
		return 8;
	}

	int operator+(int a)
	{
		return 10;
	}
};

class B1 : public A1
{
public:
	int operator-(int a)
	{
		return 5;
	}
};

int main1()
{
	B1 v;
	cout << (v + 100) << endl; // OK, print 10
	cout << (v - 100) << endl; // OK, print 5
	//cout << (v = 2) << endl; // Error, 除了赋值运算符重载函数以外，所有的运算符重载函数都可以被派生类继承。

	system("pause");
	return 0;
}

/*
class Empty{};
和你这么写是一样的：
class Empty {
public:
Empty();                        // 缺省构造函数
Empty(const Empty& rhs);        // 拷贝构造函数

~Empty();                       // 析构函数 ---- 是否
								// 为虚函数看下文说明
Empty& operator=(const Empty& rhs);    // 赋值运算符

Empty* operator&();             // 取址运算符
const Empty* operator&() const;
};

*/

