#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <typeinfo>
using namespace std;

void test()
{
	char a = 'a';
	//	char *&p1 = &a;//这样是错误的 
	//	char **p1 = &&a;//上面就好似这样。&a已经是地址了，不能再次取地址了****************************************

	char *ch = &a;
	char *&p2 = ch;//这样就行，加一个中间变量 
	char **p3 = &ch;//ch是可以取地址的

	cout << "*p2 = " << *p2 << endl;
	cout << "**p3 = " << **p3 << endl;
}

int main()
{
	/* 发现这个问题，是由于下面这段代码 */
	char sp[] = "ABDEFGC";
	//char *&p = sp;		//这段代码执行不了   为啥呢。。原因如test   数组永远不可能是指针 

	cout << sp << endl; 		//sp 数组名是地址的偏移，是一个左值，不能被改变（相当于也是字符串首地址） 
	cout << &sp << endl;		//sp 按理来说不能取地址   可能编译器优化了吧  这里取地址就相当于是  'A' 的地址 
	cout << (void *)&sp[0] << endl;
	/*
	ABDEFGC
	0055F740
	0055F740---------可以看出这两个地址是一样的
	*/

	cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////// " << endl;

	char *sp2 = "JDFASI";
	char *&p = sp2;		//这里就完全没问题了 

	cout << &sp2 << endl;
	cout << (void *)&*(sp + 1) << endl;
	/*
	00FBFCDC
	00FBFCDC--------地址一样--？？？？  原因是：本身字符串就在常量区也就是.rodata段 没有分配内存，就像 数字 1 一样。你想打印地址也没们
	*/

	cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////// " << endl;

	char *sp3 = new char[10];
	strcpy(sp3, "JDFASI");
	cout << &sp3 << endl;
	cout << (void *)&(*sp) << endl;
	/*
	0039F700
	0039F724------这样就不一样了吧
	*/

	getchar();
}