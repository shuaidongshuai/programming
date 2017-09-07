#include <iostream>
#include <vld.h>
using namespace std;

class Test
{
public:
	Test() :p(new int(5)), q(new double(15.0))
	{
		cout << "test()" << endl;
		throw exception("构造失败");//这抛出异常之后，Test这个类不会被析构了，因为根本就没有构造好
	}
	~Test()
	{
		cout << "~Test()" << endl;
	}
private:
	auto_ptr<int> p;	//使用智能指针构造之后会自动析构，这个类抛出异常只是这个类不能正常构造析构，但是这个类的成员和基类都是可以析构的
	auto_ptr<double> q;	//其实使用自定义的类也可以，可以自定义一个析构函数，但是内置类型没有析构函数，所以使用智能指针			
};

class Test2
{
public:
	Test2() :p(new int(5)), q(new double(15.0))
	{
		cout << "test()" << endl;
		throw exception("构造失败");//这抛出异常之后，Test这个类不会被析构了，因为根本就没有构造好
	}
	~Test2()
	{
		cout << "~Test()" << endl;
	}
private:
	int* p;
	double* q;
};

int main()
{
	try
	{
		Test t;
	}
	catch (const exception &err)
	{
		cout << err.what() << endl;
	}
	//上面没有内容泄漏
	//下面Visual Leak Detector detected 2 memory leaks.
	try
	{
		Test2 t;
	}
	catch (const exception &err)
	{
		cout << err.what() << endl;
	}
}