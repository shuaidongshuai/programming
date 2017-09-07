#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

class A
{
	int age;
	char* name;
public:
	A()
	{
		cout << "A()" << endl;
		age = -1;
		name = new char[1];
		*name = '\0';
	}
	A(int a)
	{
		cout << "A(int a)" << endl;
		age = a;
		name = new char[1];
		*name = '\0';
	}
	A(char* n, int a)
	{
		cout << "A(char* n, int a)" << endl;
		age = a;
		name = new char[strlen(n) + 1];
		strcpy(name, n);
	}
	A(const A &a)
	{
		cout << "A(const A &a)" << endl;
		age = a.age;
		name = new char[strlen(a.name) + 1];//1.注意：name是私有为什么也能访问？
		strcpy(name, a.name);				//答：他们是用同一个类，共享代码段
	}
	void operator=(const A &a)
	{
		cout << "operator=" << endl;

		//防止自赋值
		if (this == &a)
			return;

		//释放当前资源
		delete[] name;
		name = NULL;

		age = a.age;
		name = new char[strlen(a.name) + 1];//1.注意：name是私有为什么也能访问？
		strcpy(name, a.name);
	}
	~A()
	{
		cout << "~A()" << endl;
		delete[] name;
		name = NULL;
	}
	void show()
	{
		cout << "name :" << name << "\tage :" << age << endl;
	}
};

void test()
{
	A a1("陈", 20);
	A a2(a1);//如果自定义了析构函数，然后没有深拷贝，这会析构同一片内存两次
	A a3;
	a3 = a1;//如果自定义了析构函数，然后没有自定义operator=函数，这会析构同一片内存两次，相当于浅拷贝

	a1 = a1;//如果 operator= 中没有对这种情况处理，也会中断
}

/*显示，隐式，生成临时对象*/
void test2()
{
	/*显示生成临时对象*/
	A a1 = A("dong", 20);
	/*
	等价于  A a1("dong",20);
	A(char* n, int a)  所以只构造一次
	~A()
	*/
}
void test3()
{
	/*和上面比较一下*/
	A a1;
	a1 = A("dong", 22);
	/*
	A()					//先是 a1 构造
	A(char* n, int a)	然后是临时对象构造
	operator=			然后a1调用= 赋值
	~A()				临时对象析构
	~A()				a1析构
	*/

	a1 = 22;
	/*
	~A()		//先清空内存
	A(int a)	再构造
	*/
}
void test4()
{
	/*隐式生成临时对象*/
	A a1 = 90;
	/*
	A(int a)		//会去匹配默认构造函数中第一个参数是int 的构造函数
	~A()
	*/
	A a2 = (A)("东", 40);//和上面等价。为什么呢？  答：逗号表达式
}
/*临时对象生存周期的问题*/
void test5()
{
	A *p = &A("dong", 22);
	cout << "-----------------" << endl;

	A * const p2 = &A("ming", 22);
	cout << "-----------------" << endl;

	A &p3 = A("hello", 25);
	cout << "-----------------" << endl;

	/*
	A(char* n, int a)
	~A()				这条语句完就析构了
	-----------------
	A(char* n, int a)
	~A()				这条语句完就析构了
	-----------------
	A(char* n, int a)
	-----------------	//从这里看出，引用和指针还是有比较大的区别的，并且引用不能等价于 const A *p
	~A()				// 在这里才析构，说明，临时对象的生存周期变长了，变成了p3的生存周期
	*/
}
void test7(A *p)
{
	p->show();
}
void test6()
{
	/*深入理解临时对象生存周期的问题*/
	test7(&A("dong", 22));
	/*
	A(char* n, int a)
	name :dong      age :22
	~A()							在这个地方才析构，原因：test7(&A("dong", 22));这条语句并没有执行完
	*/
}

/*综合练习*/
A a1("dong", 20);
void test8()
{
	A a2("hello", 12);
	A a3 = a2;
	static A a4 = A("nice", 30);

	a2 = A("you", 50);
	a2 = (A)("me", 20);
	a2 = 666;

	A *p1 = &A("chen", 55);
	A &q1 = A("ming", 66);

	A *p2 = new A;
	delete p2;
	/*下面是自己先思考的答案：
	a1构造
	a5构造
	a4构造---------------这里错了，就算是static也是一行一行的执行，不会像全局变量一样提前执行
	a2构造
	a3拷贝构造
	显示临时对象构造	
	a2 operator=
	a2内存释放
	显示临时对象析构
	a2 operator=
	a2内存释放
	------------隐式构造	//下面没检验了 看花了  注意：隐式临时对象也会调用构造函数
	a2 operator=
	a2内存释放
	------------隐式析构
	p1构造
	p1析构
	q1构造
	p2构造
	p2析构
	q1
	a2
	a3
	a4
	a5
	a1析构
	*/
}
A a5("a4", 60);
int main()
{
	//test();
	//test2();
	//test3();
	//test4();
	//test5();
	//test6();

	test8();

	system("pause");
}

/*
一个类中有默认：
构造函数
析构函数
拷贝构造函数
=赋值运算符函数**********所以 = 赋值运算符不能继承，因为子类都默认有一个=函数覆盖了

A a1("dong",20);
A a2(a1)			 等价于 A a2 = a1 这叫 初始化
A a3;
a3 = a1;			这叫赋值，会调用 operator=

*/