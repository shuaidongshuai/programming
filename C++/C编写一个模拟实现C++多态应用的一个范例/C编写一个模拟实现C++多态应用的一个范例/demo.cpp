#include <iostream>
using namespace std;

// 几个基本的函数，对应抽象类中的虚函数
// 
void foo1()
{
	printf("anything foo1 \r\n");
}
void foo2(int i)
{
}
void foo3(int i, int j)
{
}
// 虚表，包含了虚函数的指针
typedef struct Vtbl
{
	void(*pf1)();
	void(*pf2)(int);
	void(*pf3)(int, int);
}Vtbl;

// 类的虚表
Vtbl g_vtbl = { &foo1, &foo2, &foo3, };

// 基类，开始处是虚表指针，
// 后面是结构成员。
typedef struct Anything
{
	//Vtbl *pvtbl;
	void *pvtbl;
	int field1;
	int field2;
}Anything;

// 构造函数
// 也是一个普通的成员函数，需要一个this指针
void InitAnything(Anything *p)
{
	p->pvtbl = &g_vtbl;
	p->field1 = 0x1234;
	p->field2 = 0x5678;
}

// 子类中的虚函数，重载了父类中的同类型函数
void Sfoo1()
{
	// 可以考虑调用父类中的函数
	// foo1();
	printf("something foo1 \r\n");
}

void Sfoo4(char *s)
{
	printf("hello %s\r\n", s);
}

// 子类中的虚表，因为内存布局是一样的，
// 直接使用父类的
typedef struct SVtbl
{
	Vtbl vtbl;
	void(*pf4)(char *);
}SVtbl;

// 子类的虚表
SVtbl g_svtbl = { { &Sfoo1, &foo2, &foo3, }, &Sfoo4, };
// 某个子类，包含父类的内容
// 还有自己的成员
typedef struct Something
{
	Anything a;
	int field3;
}Something;

// 构造函数
// 也是一个普通的成员函数，需要一个this指针
void InitSomething(Something *p)
{
	InitAnything((Anything*)p);

	p->a.pvtbl = &g_svtbl;
	p->field3 = 0xabcd;
}

void TestPolymorphism(Anything *p)
{
	// 虽然使用的是父类型的指针
	// 但虚函数最终会根据对象的真实类型调用。
	(*((Vtbl*)p->pvtbl)->pf1)();
}

void TestVtbl()
{
	// 子类的一个对象
	Something s;
	Anything *p = 0;

	// 初始化
	InitSomething(&s);

	p = (Anything*)&s;

	// 调用Sfoo4
	((SVtbl*)p->pvtbl)->pf4("Sfoo4");

	// 测试多态
	TestPolymorphism((Anything*)&s);
}

int main1()
{
	TestVtbl();

	system("pause");
	return 0;
}