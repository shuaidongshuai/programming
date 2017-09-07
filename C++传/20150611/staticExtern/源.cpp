//：：当前文件的static，再是跨文件的extern
//匿名结构体等同于全局变量， 可以跨文件，：：屏蔽匿名
#include<iostream>
using namespace std;
extern int a;//引用外部全局变量
static int a = 123;

namespace std
{
	int a = 99;//“a”: 不明确的符号
}

void main()
{
	//cout << a << endl;
	cout << ::a << endl;
	void test();
	test();

	cin.get();
}
