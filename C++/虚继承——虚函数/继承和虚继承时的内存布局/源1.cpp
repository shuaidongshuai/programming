#include<iostream>
using namespace std;
class Parent1
{
public:
	int age;
	Parent1() :age(10){}
	virtual void f(){ cout << "Parent::f()" << endl; }
	virtual void g(){ cout << "Parent::g()" << endl; }
};

int main2()
{
	cout << sizeof(Parent1) << endl;
	getchar();
	return 0;
}