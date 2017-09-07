#include <iostream>
#include <cstring>
using namespace std;

struct A
{
	int a;
	char *b;
}*p;

void test()
{
	cout << p << endl;
	cout << p + 1 << endl;//加的是整个 struct 大小
	cout << (unsigned int)p + 1 << endl;//转成 unsigned int 和 int 都一样   步长为1
	cout << (unsigned int *)p + 1 << endl;//步长为4
	/*
	00000000
	00000008
	1
	00000004
	*/
	cout << &p << endl;
	cout << &p + 1 << endl;			//相当于转成了指针 步长为4
	cout << (int*)&p + 1 << endl;	//转成了指针 步长为4
	cout << (int)&p + 1 << endl;	//步长为1
	/*
	00B4F320
	00B4F324
	00B4F324
	11858721
	*/
}
int main()
{

	test2();

	system("pause");
}