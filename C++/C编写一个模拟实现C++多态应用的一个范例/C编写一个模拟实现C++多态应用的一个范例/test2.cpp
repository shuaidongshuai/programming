#include <stdio.h>
#include <stdlib.h>


//模拟一个类A
typedef struct A
{
	void *vptr;//虚函数指针
}A;

//实现虚函数
void dong1()
{
	printf("基类  dong1\n");
}
void dong2()
{
	printf("基类  dong2\n");
}

//模拟虚表结构
typedef struct
{
	void(*v1)();
	void(*v2)();
}Vtable;

//模拟一个类中的虚表
Vtable A_Vtable = { &dong1, &dong2 };//精华在这：★a类可以调用dong1  dong2 这两个函数★

//模拟A类的构造函数
void initA(A *p)//第一个是this指针，在c++中也会默认传一个this指针
{
	p->vptr = &A_Vtable;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

//模拟派生类 B
typedef struct B
{
	A a;//*****************这是必须的。第是能给A类指针初始化，二是为了B强转为A之后能操作A中的指针
	//这样定义，也相当于在B中也有了一个void *p 的类型
}B;
//模拟派生类的虚函数
void dong11()//模拟覆盖dong1这个函数
{
	printf("派生类  dong11\n");
}
void dong66()
{
	printf("派生类  dong66\n");
}
//模拟子类虚表，增加了一个函数dong66
typedef struct
{
	Vtable vtable;
	void(*p)();
}Vtable2;

//子类的虚表
Vtable2 B_vtable = { { &dong11, &dong2 }, &dong66 };//注意这里大括号一个不能少  //★b类可以调用dong11  dong2 dong66 这三个函数★

//B类构造函数
void initB(B* p)//为什么要a参数呢？初始化基类
{
	p->a.vptr = &B_vtable;		//我们这里用B类自己的虚表，一个类一个虚表
}

///////////////////////////////////////////////////////////////////////////////////////////////////

//测试一下B类
void test2()
{
	//创建B类
	B *b = (B*)malloc(sizeof(B));
	initB(b);

	printf("%d\n", b);
	printf("%d\n", b->a);
	printf("%d\n", b->a.vptr);
	printf("%d\n", ((A*)b)->vptr);
	A* a = (A*)b;
	printf("%d\n", a->vptr);
	/*
	11961744
	20217864
	20217864
	20217864
	11961744
	*/

	

}

int main()
{
	test2();
	system("pause");
	return 0;
}

//#include <iostream>
//using namespace std;
//
//class A{};
//class B :public A{};
//class C
//{
//	A a;
//	B b;
//};
//int main()
//{
//	cout << sizeof(A) << endl;
//	cout << sizeof(B) << endl;
//	cout << sizeof(C) << endl;
//	system("pause");
//}

/*
通用链表



*/