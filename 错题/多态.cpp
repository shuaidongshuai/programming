#include <iostream>
using namespace std;

class A
{
public:
	virtual test()				//注意：调用test的时候会传入 调用者的this指针 
	{
		show1();				//这里都是 this->show1(); 所以这里调动的是B类的方法 
		show2();				//所以这里的show2没有加入到虚表，子类没有重写它，只是覆盖了它 
	}
	virtual void show1()
	{
		cout<<"A show1"<<endl;
	}
	void show2()
	{
		cout<<"A show2"<<endl;
	}
};
class B : public A
{
public:
	virtual void show1()
	{
		cout<<"B show1"<<endl;
	}
	void show2()
	{
		cout<<"B show2"<<endl;
	}
};
int main()
{
	B b;
	b.test();//注意这里用fastcall调用约定把this指针给传进去了 
	/*
	B show1
	A show2
	*/
	//尽管没有指针和引用也发生了多态 
	
	
	return 0;
}
