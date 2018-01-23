#include <iostream>
using namespace std;

template<typename T>
class Singleton
{
private:
	Singleton(){}
	virtual ~Singleton(){}
	static T *instance;
public:
	static T *getInstence(){ return instance; }
};
template<typename T>
T *Singleton<T>::instance = new T;

class A
{
protected:
	A(){}
	~A(){}
	friend Singleton<A>;
	//friend A *Singleton1<A>::getInstance();//这样也可以
public:
	int data;
	void show(){ cout << "A data = " << data << endl; }
};
class B
{
private:
	B(){}
	~B(){}
	friend Singleton<B>;
public:
	int data;
	void show(){ cout << "B data = " << data << endl; }
};

void test()
{
	A *a = Singleton<A>::getInstence();
	a->data = 1;
	a->show();
	a->data = 2;
	
	A *a2 = Singleton<A>::getInstence();
	a2->show();

	B *b = Singleton<B>::getInstence();
	b->data = 10;
	b->show();
	b->data = 20;

	B *b2 = Singleton<B>::getInstence();
	b2->show();
}
/*
A data = 1
A data = 2
B data = 10
B data = 20
*/
int main()
{
	test();
}
