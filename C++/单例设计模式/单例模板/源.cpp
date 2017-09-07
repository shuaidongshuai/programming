#include <iostream>
#include "Singleton1.h"
#include "Singleton2.h"
using namespace std;

class A :public Singleton1<A>
{
public:
	void show()
	{
		cout << "show" << endl;
	}
	//friend class Single<A>;//需要声明为友元父类才能访问
	friend A *Singleton1<A>::getInstance();//这样也可以
private:
	A(){}
	~A(){}
};
class B :public Singleton2<B>
{
public:
	void show()
	{
		cout << "show" << endl;
	}
	friend class Singleton2<B>;//需要声明为友元父类才能访问
private:
	B(){}
	~B(){}
};

int main()
{
	A *a = A::getInstance();
	a->show();

	B *b = B::getInstance();
	b->show();

	system("pause");
	return 0;
}
