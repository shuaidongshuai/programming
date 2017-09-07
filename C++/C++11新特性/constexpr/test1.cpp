#include<iostream>
using namespace std;

void test0()
{
	const int a = 2;		//在test0这个函数内，所有a都会在编译的时候被替换为2
	int *p = (int *)&a;
	*p = 20;
	cout << a << endl;//2
}
void test()
{
	int b = 2;
	const int a = b;
	int *p = (int *)&a;
	*p = 20;
	cout << a << endl;//20
}

int size()
{
	return 2;
}
void test2()
{
	int b = 2;
	const int a = size();		//如果要引用一个函数返回值，a就是一个常变量了（不是常量了）。如何让a变成常量呢？
	int *p = (int *)&a;
	*p = 20;
	cout << a << endl;//20
}
//constexpr默认是内联的，因为需要在编译时就展开（里面全是常量，可以在编译期就展开）
/*constexpr*/ int size2()	//return有且只能有一个
{
	return 2;			//★★★★★★★★★★★★★vs下面好像不支持constexpr★★★★★★★★★★★★★★★
}
void test3()
{
	int b = 2;
	const int a = size2();
	int *p = (int *)&a;
	*p = 20;
	cout << a << endl;//2
}