#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <typeinfo>
using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////////
int test()
{
	static int a = 10;
	return a;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct dong
{
	int data;
}Dong;
Dong test2()
{
	static Dong d = { 10 };
	return d;/*						00FC51E5  mov         eax,dword ptr [d]  也是通过eax寄存器把返回值带出去
			 后来加上的static    001C51DE  mov         eax,dword ptr ds:[001CF00Ch]  都一样 eax寄存器带出去*/
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
class A				/*没有自定义构造函数的类，就相当于结构体，属于自定义类型*/
{
public:

	int data;
};
A test3()
{
	static A a;
	return a;/*0102524E  mov         eax,dword ptr ds:[0102F358h] */
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
class B
{
public:
	int data;
	B(){}		//自定义一个空构造函数 和系统默认的构造函数一样  编译的结构也是大不一样
};
B test4()
{
	static B b;
	return b;
}
int main()
{
	//int &a = test();		//使用eax寄存器返回来的值，是一个立即数，咋可能被引用

	Dong &d = test2();		//这个为什么可以呢
	/*
	00995398  call        test2 (09911CCh)
	0099539D  mov         dword ptr [ebp-0E4h],eax		在return 之后产生了一个临时量 把 eax值给这个临时量
	009953A3  mov         eax,dword ptr [ebp-0E4h]
	009953A9  mov         dword ptr [ebp-18h],eax
	009953AC  lea         ecx,[ebp-18h]
	009953AF  mov         dword ptr [d],ecx
	*/

	A &a = test3();
	/*
	01027F42  call        test3 (0102142Eh)
	01027F47  mov         dword ptr [ebp-0FCh],eax		在return 之后产生了一个临时量 把 eax值给这个临时量
	01027F4D  mov         eax,dword ptr [ebp-0FCh]
	01027F53  mov         dword ptr [ebp-30h],eax
	01027F56  lea         ecx,[ebp-30h]
	01027F59  mov         dword ptr [a],ecx
	*/

	B &b = test4();
	/*
	00267F8C  lea         eax,[ebp-48h]
	00267F8F  push        eax
	00267F90  call        test4 (0261438h)		在进入函数之前，就已将创建了一个临时量。并把临时量压栈，作为参数传递给函数
	00267F95  add         esp,4
	00267F98  lea         ecx,[ebp-48h]
	00267F9B  mov         dword ptr [b],ecx
	*/


	getchar();
}