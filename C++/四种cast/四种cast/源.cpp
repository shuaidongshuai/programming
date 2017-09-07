#include <iostream>
using namespace std;

class Base
{
public:
	int _base;
	virtual void printinfo()
	{
		cout << _base << endl;
	}
};

class Derived : public Base
{
public:
	int _derived;
	virtual void printinfo()
	{
		cout << _derived << endl;
	}
};

int main(void)
{
	Base b1;
	Derived d1;
	int aInt = 10;
	long aLong = 11;
	float aFloat = 11.11f;
	double aDouble = 12.12;

	Derived* pd = static_cast<Derived*>(&b1);		  // down-casting          不安全
	Base* pb = static_cast<Base*>(&d1);               // up-casting                安全
	Derived& d = static_cast<Derived&>(b1);          // down-casting          不安全
	Base& b = static_cast<Base&>(d1);				   // up-casting                安全

	aInt = static_cast<int>(aFloat);				   // 基本数据类型转换
	void* sth = static_cast<void*>(&aDouble);           // 将double指针类型转换成void指针类型
	double* bDouble = static_cast<double*>(sth);        // 将void指针类型转换成double指针类型
	cout << *bDouble << endl;

	Base* pb1 = dynamic_cast<Base*>(&d1);
	Derived* pd1 = dynamic_cast<Derived*>(&b1);     // 编译时有warning，运行时出错

	int bInt = reinterpret_cast<int>(pb1);             // 将地址或指针转换成整数
	cout << bInt << endl;
	pb1 = reinterpret_cast<Base*>(bInt);                // 将整数转换成地址或指针

	int* cInt = reinterpret_cast<int*>(&aFloat);    // 这个转换的结果会出乎意料
	cout << (int)*cInt << endl;

	const Base* bBase = new Base();
	Base* cBase = const_cast<Base*>(bBase);
	//Base* dBase = dynamic_cast<Base*>(bBase);                // 不能通过编译
	//Base* eBase = static_cast<Base*>(bBase);                     // 不能通过编译
	//Base* fBase = reinterpret_cast<Base*>(bBase);             // 不能通过编译


	cin.get();
	return 0;
}