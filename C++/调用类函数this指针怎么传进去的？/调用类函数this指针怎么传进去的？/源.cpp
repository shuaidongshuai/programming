#include <iostream>
using namespace std;

class A
{
public:
	int a;
	long long b;
	void test()
	{
		a = 10;
		b = 20;
	}
	void test2(int c)
	{
		a = c;
	}
};

int main()
{
	A a;
	int b = 10;
	a.test();
	//a.test2(b);
	return 0;
}
/*
A a;
a.test();
00F45318  lea         ecx,[a]						//通过ecx把this指针传进去的
00F4531B  call        A::test (0F4116Dh)

class A
{
public:
int a;
int b;
void test()
{
00BA51B0  push        ebp
00BA51B1  mov         ebp,esp
00BA51B3  sub         esp,0CCh
00BA51B9  push        ebx
00BA51BA  push        esi
00BA51BB  push        edi
00BA51BC  push        ecx
00BA51BD  lea         edi,[ebp-0CCh]
00BA51C3  mov         ecx,33h
00BA51C8  mov         eax,0CCCCCCCCh
00BA51CD  rep stos    dword ptr es:[edi]
00BA51CF  pop         ecx
00BA51D0  mov         dword ptr [this],ecx				//ecx把传进来的值赋给 创建的this指针
00BA51D0  mov         dword ptr [ebp-8],ecx	//不显示符号****  这里this指针就是ebp-8   然而ebp+8才是传进来的第一个参数
a = 10;
00BA51D3  mov         eax,dword ptr [this]
00BA51D6  mov         dword ptr [eax],0Ah	//顺便发现了，类中访问a变量，是通过this指针来访问的，加上一定的偏移值就是变量a的值。这里a的地址就是类的基址，就是this指针的地址
b = 20;
00BA51DC  mov         eax,dword ptr [this]
00BA51DF  mov         dword ptr [eax+4],14h	//这里偏移值是 4  *************************
}
00BA51E6  pop         edi
00BA51E7  pop         esi
00BA51E8  pop         ebx
00BA51E9  mov         esp,ebp
00BA51EB  pop         ebp
}
00BA51EC  ret

-----------------------------------------------------------------------------------

A a;
int b = 10;
003154E8  mov         dword ptr [b],0Ah
//a.test();
a.test2(b);
003154EF  mov         eax,dword ptr [b]
003154F2  push        eax
003154F3  lea         ecx,[a]
003154F6  call        A::test2 (0311429h)

void test2(int c)
{
003153B0  push        ebp
003153B1  mov         ebp,esp
003153B3  sub         esp,0CCh
003153B9  push        ebx
003153BA  push        esi
003153BB  push        edi
003153BC  push        ecx
003153BD  lea         edi,[ebp-0CCh]
003153C3  mov         ecx,33h
003153C8  mov         eax,0CCCCCCCCh
003153CD  rep stos    dword ptr es:[edi]
003153CF  pop         ecx
003153D0  mov         dword ptr [this],ecx
003153D0  mov         dword ptr [ebp-8],ecx		*** 还是 ebp-8   最后一个压入栈的（第一个形参，第一个实参）
a = c;
003153D3  mov         eax,dword ptr [this]
003153D6  mov         ecx,dword ptr [c]
003153D6  mov         ecx,dword ptr [ebp+8]		*** 
003153D9  mov         dword ptr [eax],ecx
}
*/