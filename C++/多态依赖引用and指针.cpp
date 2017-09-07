#include <iostream>
using namespace std;

class A
{
public:
	A(){
		cout<<"aaa"<<endl;
	}
	A(const A &a)
	{
		cout<<"A拷贝构造"<<endl;
	}
	virtual void dong()
	{
		cout<<"AAAAAAAAAAAAAAAAAAAAAAAAA"<<endl;
	}
};
class B : public A
{
public:
	B(){
		cout<<"bbb"<<endl;
	}
	B(const B &a)
	{
		cout<<"B拷贝构造"<<endl;
	}
		virtual void dong()
	{
		cout<<"BBBBBBBBBBBBBBBBBBBB"<<endl;
	}
};

void test1(A *a)
{
	a->dong();
}
void test2(A &a)
{
	a.dong();
}
void test3(A a)
{
	a.dong();
}

int main()
{
	A* a = new B;
	test1(a);
	cout<<"------------------------------"<<endl;
	test2(*a);
	cout<<"------------------------------"<<endl;
	test3(*a);
}
/*
aaa
bbb
BBBBBBBBBBBBBBBBBBBB
------------------------------
BBBBBBBBBBBBBBBBBBBB
------------------------------
A拷贝构造								//调用的是A的拷贝构造 
AAAAAAAAAAAAAAAAAAAAAAAAA				//所以对象完全就是A了   没有多态了 
*/
