#include<iostream>
using namespace std;

typedef struct dong
{
	int a[4];
}Dong;
typedef struct dong2
{
	int b;
}Dong2;
typedef struct dong3
{
	int a;
	int b;
}Dong3;
class Dong4
{
public:
	int a;
};
class Dong5
{
public:
	int a;
	int b;
};
class Dong6
{
public:
	int age;
	Dong6(){}
};
class Dong7
{
public:
	int a[4];
};
class Dong8
{
public:
	int a[4];
	Dong8(){}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////
Dong test()
{
	Dong d;
	d.a[0] = 1;
	return d;
}
Dong2 test2()
{
	Dong2 d2;
	d2.b = 6;//00F851CE  mov         dword ptr [d2],6
	return d2;//000A51D5  mov         eax,dword ptr [d2]    返回值使用eax带出来的
}
Dong3 test3()
{
	Dong3 d3;
	d3.a = 2;//00B93ACE  mov         dword ptr [d3],2 
	d3.b = 6;//00B93AD5  mov         dword ptr [ebp-8],6 
	return d3;
	/*
	00B93ADC  mov         eax,dword ptr [d3]
	00B93ADF  mov         edx,dword ptr [ebp-8]		用了 eax 和 edx 把返回值带出去
	*/
}
Dong4 test4()
{
	Dong4 d4;
	d4.a = 10;
	return d4;//00B75235  mov         eax,dword ptr [d4]  同上
}
Dong5 test5()
{
	Dong5 d5;
	d5.a = 10;
	d5.b = 20;
	return d5;
	/*
	011A533C  mov         eax,dword ptr [d5]
	011A533F  mov         edx,dword ptr [ebp-8]			同上
	*/
}
Dong6 test6()
{
	Dong6 d6;
	d6.age = 20;
	return d6;
}
Dong7 test7()
{
	Dong7 d7;
	d7.a[0] = 1;
	return d7;
}
Dong8 test8()
{
	Dong8 d8;
	d8.a[0] = 5;
	return d8;
}
void main2()
{
	Dong d = test();
	/*
	011F7F6E  lea         eax,[ebp-104h]
	011F7F74  push        eax				形参入栈
	011F7F75  call        test (011F13A7h)	在调用之前，在main中开辟了内存，产生了临时对象，并把临时对象的地址传到test()函数中
	*/
	Dong2 d2 = test2();
	/*
	013A7FC4  call        test2 (013A1429h)			在调用之前没有压栈，也就是没有参数传递
	*/
	Dong3 d3 = test3();
	/*
	00FA8038  call        test3 (0FA142Eh)			同上
	*/
	Dong4 d4 = test4();
	/*
	00D680BB  call        test4 (0D61433h)			同上
	013D612A  mov         dword ptr [ebp-138h],eax
	013D6130  mov         eax,dword ptr [ebp-138h]
	013D6136  mov         dword ptr [d4],eax
	和d6的区别在于，默认构造函数可以把值带出来进行赋值，自定义构造函数编译器不知道我们做了什么，所以不能这样做
	*/
	Dong5 d5 = test5();
	/*
	011A812F  call        test5 (011A1438h)			同上
	*/
	Dong6 d6 = test6();
	/*
	010C615C  lea         eax,[d6]
	010C615F  push        eax						我还以为创建了临时对象，结果仔细一看不对，它只是把指向d6内存指针给压栈了，传进去了，目的，节约内存，直接在函数中进行构造
	010C6160  call        test6 (010C101Eh)		    相当于 Dong6 d6 = d6  等价于  Dong6 d6(d6)
	和d4的区别在于，d6有自定义的构造函数，需要调用自己的构造函数
	*/
	Dong7 d7 = test7();
	/*
	00A16418  lea         eax,[ebp-14Ch]			发现和d6的区别了么？？？？  这里创建了临时对象
	00A1641E  push        eax
	00A1641F  call        test7 (0A114D3h)
	*/ 
	Dong8 d8 = test8();
	/*
	00CB649E  lea         eax,[d8]
	00CB64A4  push        eax
	00CB64A5  call        test8 (0CB14DDh)			和d6一模一样
	*/
	/*
	在这里就可以总结了：当没有自定义构造函数的时候，函数返回一个对象（内存大于8的话）需要在调用函数中创建临时对象
	如果有了自定义构造函数，那么直接把d8这个对象地址传进去，在函数里面直接就初始化了，根本不需要带出来，也就不产生临时量
	★为什么没有自定义构造，内存大于8会产生临时对象
	★定义了构造函数，绝对不会产生临时对象
	*/

	/*----------------上面试初始化过程--------------------------------下面是赋值过程----------------*/

	Dong4 d41;								//没有自定义构造函数
	d41 = test4();
	/*
	00D85BFD  call        test5 (0D81320h) 
	*/
	Dong7 d71;								// 和d41比，内存大于8 字节了
	d71 = test7();
	/*
	00AE9BE4  lea         eax,[ebp-1B8h]
	00AE9BEA  push        eax
	00AE9BEB  call        test7 (0AE14C4h)
	*/
	Dong6 d61;								// 和d41比，有自定义构造函数
	d61 = test6();
	/*
	00D75C08  lea         eax,[ebp-17Ch]
	00D75C0E  push        eax
	00D75C0F  call        test6 (0D7101Eh)
	*/
	Dong8 d81;								//和d61比，内存大于8字节
	d81 = test8();
	/*
	01265C08  lea         eax,[ebp-1E4h]  
	01265C0E  push        eax  
	01265C0F  call        test8 (012612D5h)  
	*/
	/*
	★总结：赋值运算，只要有自定义构造，就会产生临时对象，没有自定义构造，大于8字节才会产生临时对象

	有自定义构造函数，和没有自定义构造函数的区别：
	有自定义构造函数就需要传入这个对象的地址，也就是this指针，如果没有自定义构造函数，也就不需要传this指针，也就不需要这个对象的地址
	*/
	getchar();
}
/*
最终的总结：初始化过程------基本都不会产生临时量，只有"没有构造函数"且"内存大于8字节"才“会”产生临时量
			赋值过程--------基本都会产生临时量，  只有"没有构造函数"且“内存小于8字节”才“不会”产生临时量
*/