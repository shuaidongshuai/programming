#include <iostream>
using namespace std;
//__cdecl 是 C Declaration 的缩写，表示 C 和 C++ 默认的函数调用约定。是C/C++和MFCX的默认调用约定。
int _cdecl mul(int a, int b)	//c调用约定
{
	return a*b;
}
//_stdcall是Standard Call的缩写，是C++的标准调用方式, 当然这是微软定义的标准，__stdcall通常用于Win32 API中(可查看WINAPI的定义)。
int _stdcall aaa(int a, int b)	//windows标准的调用约定
{
	return a + b;
}
//_fastcall调用的主要特点就是快，因为它是通过寄存器来传送参数的。
//。注意通过寄存器传送的两个参数是从左向右的
int _fastcall bbb(int a, int b)	//快速调用约定
{
	return a + b;
}

int main()
{
	int a = 1;
	int b = 2;
	int c;
	cout << sizeof(int *) << endl;
	c = bbb(a, b);

	system("pause");
	return 0;
}
//
//总结
//
//这里主要总结一下_cdecl、_stdcall、__fastcall三者之间的区别：
//
//要点				__cdecl				__stdcall				__fastcall
//参数传递方式		右->左				右->左					左边开始的两个不大于4字节（DWORD）的参数分别放在ECX和EDX寄存器，其余的参数自右向左压栈传送
//清理栈方			调用者清理			被调用函数清理			被调用函数清理
//适用场合		C/C++、MFC的默认方式; 可变参数的时候使用;		Win API	要求速度快
//C编译修饰约定		_functionname		_functionname@number	@functionname@number