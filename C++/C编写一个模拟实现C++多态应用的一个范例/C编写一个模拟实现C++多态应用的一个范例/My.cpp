#include <stdio.h>
#include <stdlib.h>


//模拟一个类A
typedef struct A
{
	void *vptr;//虚函数指针

	//下面内容可以删掉，写上的目的：看着像一个类
	int a;//成员变量
	int b;
	void initA(A *p, int a, int b);
	void dong1();//虚函数
	void dong2();
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
void initA(A *p, int a, int b)//第一个是this指针，在c++中也会默认传一个this指针
{
	p->vptr = &A_Vtable;
	p->a = a;
	p->b = b;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

//模拟派生类 B
typedef struct B
{
	A a;//父类的内容

	//下面内容可以删掉，写上的目的：看着像一个类
	int b;
	void dong11();
	void dong66();
	void initB(B* p, int a, int b);
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
void initB(B* p,int a, int b)//为什么要a参数呢？初始化基类
{
	//************重点**************
	//initA((A*)p, a, b);			//创建B类，但是需要初始化A类。继承A类中的虚表指针
	p->a.vptr = &B_vtable;		//我们这里用B类自己的虚表，一个类一个虚表
	p->b = b;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

//以下内容全是模拟

//测试一下A类
void test1()
{
	A aa;
	initA(&aa, 10, 20);
	((Vtable*)aa.vptr)->v1();
	((Vtable*)aa.vptr)->v2();
}
//测试一下B类
void test2()
{
	//创建B类
	B *b = (B*)malloc(sizeof(B));
	initB(b, 10, 20);

	//转成A类
	A *a = (A*)b;
	((Vtable2*)(a->vptr))->p();//现在表面上是父类，而我们可以调用父类没有而子类有的方法

	printf("\n------见证奇迹的时候到了，实现多态------\n\n");

	((Vtable*)(a->vptr))->v1();		//子类覆盖了父类对象，调用的就是子类对象
	((Vtable*)(a->vptr))->v2();		//子类没有覆盖父类对象，调用的就是父类对象
}
//test3用来解惑的。其实我们b类不靠A就能调用父类，子类方法，test2实现的多态就是为了模拟C++
void test3()
{
	B *b = (B*)malloc(sizeof(B));
	initB(b, 10, 20);

	//下面两个地址是一样的，这里得仔细考虑。我也是调试了好久才发现其中的奥秘
	printf("%d\n", b->a.vptr);
	printf("%d\n", ((A*)b)->vptr);

	((Vtable*)(b->a.vptr))->v1();	
	((Vtable*)(b->a.vptr))->v2();
	((Vtable2*)(b->a.vptr))->p();
}
int main()
{
	test1();
	printf("---------------------------------------------\n\n");
	test2();
	printf("---------------------------------------------\n\n");
	test3();
	system("pause");
	return 0;
}
/*
基类  dong1
基类  dong2
---------------------------------------------

派生类  dong66

------见证奇迹的时候到了，实现多态------

派生类  dong11
基类  dong2
---------------------------------------------

12185644
12185644
派生类  dong11
基类  dong2
派生类  dong66
*/
/*
**************************上面看着费劲----光看下面就行了**************************
typedef struct
{
	void(*v1)();
	void(*v2)();
}Vtable;

Vtable A_Vtable = { &dong1, &dong2 };	//如果不单独测试A 这句话就是废话

typedef struct
{
	Vtable vtable;		//Vtable2有一个Vtable，所以Vtable2可以转化为Vtable使用v1 v2。 
	void(*p)();			//但是我们赋值的时候是Vtable2  所以真真调用的时候，还是从Vtable2中调用
}Vtable2;

Vtable2 B_vtable = { { &dong11, &dong2 }, &dong66 };

所以，至始至终我们利用的就是Vtable2指向的函数。可以调用v1那是因为Vtable2中有Vtable，而Vtable中有v1
*/