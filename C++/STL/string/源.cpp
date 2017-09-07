#define D_SCL_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

//string ==>  char*
void test1()
{
	string str = "abc";
	char* p;
	p = (char *)str.c_str();
	cout << "str.c_str() = " << str.c_str() << endl;
	cout << "p = " << p << endl;

	*p = 'A';//因为指向同一片内存，所以下面都变成了Abc
	cout << "--------------" << endl;
	cout << "str.c_str() = " << str.c_str() << endl;
	cout << "p = " << p << endl;
}
//const char* ==> string    其实 string s = "dong"就是const char* ==> string
void test2()
{
	string str1 = "abc";
	string str2;
	str2 = str1.c_str();

	cout << "str1 = " << str1 << "     str2 = " << str2 << endl;
}
//string 子串
void test3()
{
	string str1 = "123456789";
	string str2;
	string str3;

	//可以简单的做一下，让这个字符串循环
	while (1)
	{
		str2 = str1.substr(0, 8);
		str3 = str1.substr(8, 1);
		str1 = str3 + str2;
		cout << str1 << endl;
		Sleep(1000);
	}
}
//字符串的查找
void test4()
{
	string str = "dong | hello | nice | to | meet | you | dong | yes | dong";
	int index = str.find("ng", 0);//从零位置开始检索		没找到返回-1
	cout << index << endl;// 2

	//求dong出现的次数
	int count = 0;
	index = str.find("dong", 0);
	while (index!=string::npos)//如果没找到，返回一个  npos取值是-1
	{
		count++;
		index = str.find("dong", index+1);
	}
	cout << "东出现的次数是：" << count << endl;
}
//字符串的替换
void test5()
{
	string str = "dong | hello | nice | to | meet | you | dong | yes | dong";
	int index = str.find("dong", 0);
	while (index != string::npos)//如果没找到，返回一个  npos取值是-1
	{
		str.replace(index, 4, "马云");//吧dong  全部替换成马云		// 1.开始位置 2.向后替换多少个字符  3.新串
		index = str.find("dong", index + 1);
	}
	cout << str << endl;
}
//删除
void test6()
{
	string str = "123456789";
	str = str.erase(0, 3);	//从0位置开始删除3个字符
	cout << str << endl;//456789
}
//删除2
void test7()
{
	string str = "dong | hello | nice | to | meet | you | dong | yes | dong";
	int index = str.find("dong", 0);
	while (index != -1)
	{
		str.erase(index, 6);
		index = str.find("dong", index + 1);
	}
	cout << str << endl;
}
//插入
void test8()
{
	string str = "hello dong";
	str.insert(5, " chen ming");//在 4  后面  5 前面 插入
	cout << str << endl;
}
int test9();
int test10();
int test11();

int main()
{
	//test1();
	//test2();
	//test3();
	//test4();
	//test5();
	//test6();
	//test7();
	//test8();
	//test9();
	//test10();
	test11();

	system("pause");
	return 0;
}