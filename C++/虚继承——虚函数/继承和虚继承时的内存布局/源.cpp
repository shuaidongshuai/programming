#include<iostream>
using namespace std;
class Parent
{
public:
	int age;
	Parent() :age(10){}
	virtual void f(){ cout << "Parent::f()" << endl; }
	virtual void g(){ cout << "Parent::g()" << endl; }
};
class Child : public Parent
{
public:
	int num;
	Child() :num(6){}
	virtual void f(){ cout << "Child::f()" << endl; }
	virtual void h(){ cout << "Child::h()" << endl; }
	virtual void gc(){ cout << "Child::gc()" << endl; }
};
class GrandChild : public Child
{
public:
	int gpa;
	GrandChild() : gpa(4){}
	virtual void f(){ cout << "GrandChild::f()" << endl; }
	virtual void ggc(){ cout << "GrandChild::ggc()" << endl; }
	virtual void gc(){ cout << "GrandChild::gc()" << endl; }
};

int main()
{
	typedef void(*Func)(void);
	GrandChild temp;
	Parent *p = new GrandChild();
	int ** ptVtab = (int **)(&temp); //这里我们用一个二级指针指向虚表内存储的虚函数的入口地址，为什么用									int呢？跟机器相关32位的机器一个指针
	int i = 0; //占用4个字节的存储空间！
	Func f;
	for (i = 0; (Func)ptVtab[0][i] != NULL; i++)//对象内存空间的起始位置
	{
		f = (Func)ptVtab[0][i];
		f();
	}
	cout << (int)ptVtab[1] << endl;//跳过四个字节之后的位置！
	cout << (int)ptVtab[2] << endl;
	cout << (int)ptVtab[3] << endl;
	p->f();
	system("pause");
	return 0;
}
/*
GrandChild::f()
Parent::g()
Child::h()
GrandChild::gc()
GrandChild::ggc()
10
6
4
GrandChild::f()
*/