#include<iostream>
using namespace std;

class A{
public:
	void test()
	{
		cout<<"aaaaa"<<endl;
	}
	static void test2()
	{
		cout<<"BBBBBB"<<endl;
	}
	int a;
};

int main()
{
	void (*p2)() = A::test2;
	(*p2)();
	
	void (A::*p)() = A::test;		//能赋值，，但是调用不起来 
	cout<<p<<endl; 
	cout<<A::test<<endl;
	
	int A::*p3 = &A::a;				//在vs中会报错，vc和gcc中可以这样。但是这样做的意义不清楚 
}
