#include <iostream>
using namespace std;

class A
{
private:
	int a;
	static int b;
public:
	static int c;
	void test1()
	{
		this->a = 10;
	}
	friend void test2()			// 一般声明在类中，实现在外面，在里面也行
	{
		//this->a = 10;				 注意1： 友元函数中没有this指针
		cout << A::b << endl;	//	 注意2： 访问类中静态成员也必须使用A::作用域
		cout << A::c << endl;
	}
};
int A::b = 20;
int A::c = 30;

void test2();		//这里必须声明

int main()
{
	test2();
}
