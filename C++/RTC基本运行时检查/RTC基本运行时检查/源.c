
//#include <stdio.h>
//void fun1()
//{
//	int a = 48;
//}
//void fun2()
//{
//	int b;
//	printf("%d", b);
//}

//#pragma runtime_checks( "scu", off )
//#pragma runtime_checks( "cu", off )
void func(void)
{
	int data[0x10];
	//data[0x10] = 0;					// 1 * 16 * 4 = 64;
	//data[0x11] = 0;
	data[0x10] = 0xcccccccc;
}
//下面这段代码在vs2013编译不过，只要调用未初始化的值，直接就是error  以前是waring
#pragma runtime_checks( "s", off )
void func2()
{
	int data1, data2;
	data1 = data2;
}
int main()
{
	func2();

	getchar();
}
/*
#pragma runtime_checks( "scu", off )
void func(void)
{
011C1260  push        ebp
011C1261  mov         ebp,esp
011C1263  sub         esp,80h		// 80h
011C1269  push        ebx
011C126A  push        esi
011C126B  push        edi
int data[0x10];
}

#pragma runtime_checks( "cu", off )
void func(void)
{
012013C0  push        ebp
012013C1  mov         ebp,esp
012013C3  sub         esp,108h					// 108h = 264
012013C9  push        ebx
012013CA  push        esi
012013CB  push        edi
012013CC  lea         edi,[ebp-108h]			
012013D2  mov         ecx,42h					// 4 * 16 + 2 = 68  拷贝 68 次
012013D7  mov         eax,0CCCCCCCCh			// eax是4byte  所以 68 * 4 = 272  我们只需要264byte空间，但是开辟了272空间，多了8byte
012013DC  rep stos    dword ptr es:[edi]
int data[0x10];
}
012013DE  push        edx
012013DF  mov         ecx,ebp
012013E1  push        eax
012013E2  lea         edx,ds:[12013F8h]
012013E8  call        @_RTC_CheckStackVars@8 (01201087h)	//RTC_CheckStackVars的调用
012013ED  pop         eax
012013EE  pop         edx
012013EF  pop         edi
012013F0  pop         esi
012013F1  pop         ebx
012013F2  mov         esp,ebp
012013F4  pop         ebp
int data[0x10];
}
*/
/*
vs2008提供了一个叫/RTC的选项，用以控制编译器是否进行运行时检查，这个选项在C/C++ => 代码生成 => 基本运行时检查 中可以进行选择，更具体的说明可以在msdn里找到，我们更有兴趣的是它如何实现这个功能的。
首先写一个简单的C代码：
#pragma runtime_checks( "scu", off )
void func(void)
{
int data[0x10];
}
上面的代码借助于#pragma将vs的运行时检查全部关闭。因为这个运行时检查和栈相关，所以我们简单在栈上定义了一个变量，看看它生成的汇编代码：
#pragma runtime_checks( "scu", off )
void func(void)
{
00401020 55               push        ebp
00401021 8B EC            mov         ebp,esp
00401023 83 EC 40         sub         esp,40h
int data[0x10];
}
00401026 8B E5            mov         esp,ebp
00401028 5D               pop         ebp
00401029 C3               ret
符合我们的期待，它简单地将ESP指针往下减了40h个字节，这也是我们定义的data数组的大小。
1.1    堆栈帧检查

下面我们打开堆栈帧的检查，再看它的代码：
#pragma runtime_checks( "cu", off )
void func(void)
{
00401020 55               push        ebp
00401021 8B EC            mov         ebp,esp
00401023 83 EC 48         sub         esp,48h
00401026 57               push        edi
00401027 8D 7D B8         lea         edi,[ebp-48h]
0040102A B9 12 00 00 00   mov         ecx,12h
0040102F B8 CC CC CC CC   mov         eax,0CCCCCCCCh
00401034 F3 AB            rep stos    dword ptr es:[edi]
int data[0x10];
}
00401036 52               push        edx
00401037 8B CD            mov         ecx,ebp
00401039 50               push        eax
0040103A 8D 15 4C 10 40 00 lea         edx,[ (40104Ch)]
00401040 E8 8B 00 00 00   call        _RTC_CheckStackVars (4010D0h)
00401045 58               pop         eax
00401046 5A               pop         edx
00401047 5F               pop         edi
00401048 8B E5            mov         esp,ebp
0040104A 5D               pop         ebp
0040104B C3               ret
可以看到，这个时候栈的大小加大到了48h，比我们需要的多了8个字节，而且它将这块栈空间全部以0xcc进行填充。在函数的最后还多了一个对RTC_CheckStackVars的调用。
当数组越界时，比如在func函数进行如下操作：
data[0x10] = 0;
在退出函数的时候，VS将给出一个assert对话框，告诉你data这个数组可能溢出了。但很有意思的是，如果使用下面的赋值语句，VS却不会报错：
data[0x11] = 0;
同样是越界，两种不同的结果，由此可见，VS应该会为数组多分配一个元素的空间，且只检查数组的最后一个元素空间是否为0xcc。
如果我们这样设置数组的最后一个元素的值：
data[0x10] = 0xcccccccc;
同样，VS也不会报错。
原来并不神秘，VS也仅仅是实现了一个非常简单的检查，工作还得靠自己！
1.2    未初始化的变量检查

再试试未初始化的变量检查，写段代码：
#pragma runtime_checks( "s", off )
void func(void)
{
00401020 55               push        ebp
00401021 8B EC            mov         ebp,esp
00401023 83 EC 0C         sub         esp,0Ch
00401026 C6 45 F7 00      mov         byte ptr [ebp-9],0
int data1, data2;
data1 = data2;
0040102A 80 7D F7 00      cmp         byte ptr [ebp-9],0
0040102E 75 0D            jne         func+1Dh (40103Dh)
00401030 68 47 10 40 00   push        offset  (401047h)
00401035 E8 C6 06 00 00   call        _RTC_UninitUse (401700h)
0040103A 83 C4 04         add         esp,4
0040103D 8B 45 F8         mov         eax,dword ptr [data2]
00401040 89 45 FC         mov         dword ptr [data1],eax
}
可以看到，编译器在赋值语句的后面插入了一大段的汇编代码，因为在编译的时候这行赋值语句有一个警告：
f:/projects/test/cpptest/cpptest.cpp(15) : warning C4700: 使用了未初始化的局部变量“data2”
想来编译器是在有警告的地方才会插入检测的代码，给data2赋一个初值：
#pragma runtime_checks( "s", off )
void func(void)
{
00401020 55               push        ebp
00401021 8B EC            mov         ebp,esp
00401023 83 EC 08         sub         esp,8
int data1, data2 = 0;
00401026 C7 45 F8 00 00 00 00 mov         dword ptr [data2],0
data1 = data2;
0040102D 8B 45 F8         mov         eax,dword ptr [data2]
00401030 89 45 FC         mov         dword ptr [data1],eax
}
果然不再插入相关的代码。
假如data2不是局部变量而是全局变量，就像这样的：
int data2;
#pragma runtime_checks( "s", off )
void func(void)
{
00401020 55               push        ebp
00401021 8B EC            mov         ebp,esp
00401023 51               push        ecx
int data1;
data1 = data2;
00401024 A1 8C 71 40 00   mov         eax,dword ptr [data2 (40718Ch)]
00401029 89 45 FC         mov         dword ptr [data1],eax
}
这个时候VS同样不会插入检测代码。
*/