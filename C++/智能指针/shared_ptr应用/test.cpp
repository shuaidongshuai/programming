#include <iostream>
#include "MyVector.h"
#include <vector>
using namespace std;

class A
{
public:
	int id;
	A(int a) :id(a){ cout << "构造" << id << endl; }
	A(const A &a){ this->id = a.id; cout << "copy构造" << id << endl; }
	~A(){ cout << "xigou" << id << endl; }
};

void test1()
{
	A a1(1);
	A a2(2);
	vector<A> v;
	v.push_back(a1);
	v.push_back(a2);
	cout << "----------------" << endl;
	vector<A> v2 = v;
	cout << "----------------" << endl;
}
/*
构造1		a1
构造2		a2
copy构造1	push_back是进行的拷贝构造  a1
copy构造1	调整内存，还是拷贝构造	   a1
xigou1		析构先前内存上的		   a1
copy构造2	当前内存上构造			   a2
----------------
copy构造1
copy构造2
----------------
xigou1
xigou2
xigou1
xigou2
xigou2
xigou1
*/
void test2()
{
	A a1(1);
	A a2(2);
	MyVector<A> v;
	v.push_back(a1);
	v.push_back(a2);
	cout << "----------------" << endl;
	MyVector<A> v2 = v;
	cout << "----------------" << endl;
}
/*
构造1
构造2
copy构造1
copy构造1
xigou1
copy构造2
----------------
----------------
xigou1
xigou2
xigou2
xigou1
*/