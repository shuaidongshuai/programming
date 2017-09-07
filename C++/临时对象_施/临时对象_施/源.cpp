#include <iostream> 
using namespace std;

class A
{
	int age;
public:
	A(int a = 0) :age(a)
	{
		cout << "gou zhao" << endl;
	}
	A(const A &a)
	{
		cout << "拷贝构造" << endl;
	}
	void operator=(const A &a)
	{
		cout << "operator = " << endl;
		age = a.age;
	}
	~A()
	{
		cout << "析构" << endl;
	}
	int get()
	{
		return age;
	}
};


A test(A a)
{
	A aa(a.get());
	return aa;
}
A& test2(A a)
{
	A aa(a.get());
	return aa;
}
void dong()
{
	A a(10);
	A a2;
	a2 = test(a);
	cout << "----" << endl;
	A a3;
	a3 = test2(a);
	cout << "---------------------" << endl;
	/*
	gou zhao
	gou zhao
	拷贝构造		形参拷贝构造
	gou zhao		
	拷贝构造		把aa拷贝到main函数的临时量中去，也就是初始化临时对象
	析构		局部变量析构
	析构		形参析构
	operator =
	析构			临时量析构  临时量析构是在a2 = test(a);完成之后才析构的
	----			
	gou zhao
	拷贝构造
	gou zhao
	析构
	析构			//由于返回值并不需要拷贝出来，返回的是引用，所以并不产生临时对象，看下面反汇编
	operator =
	---------------------
	析构
	析构
	析构
	*/
}
/*以后要传出一个类对象，像下面这样写，高效*/
A test3(A &a)
{
	int value = a.get();
	return A(value);		//接直接临时量进行构造，和上面比 1、少了创建一个新对象的时间  2、少了一个对象 copy 到另一个对象的时间
}
void dong2()
{
	A a(10);
	A a2;
	a2 = test3(a);
	/*
	gou zhao
	gou zhao
	gou zhao		临时量构造
	operator =
	析构			临时量析构
	析构
	析构
	*/
}
void dong3()
{
	A a(10);
	A a2 = test3(a);//这样写不会产生临时对象，因为会直接在copy到a2内存上，直接初始化，dong2那个叫赋值
	/*
	gou zhao
	gou zhao
	析构
	析构
	*/
}
int main2()
{
	//dong();
	//dong2();
	dong3();

	getchar();
	return 0;
}

/*
a2 = test(a);
010C633F  lea         eax,[a]
010C6342  push        eax
010C6343  lea         ecx,[ebp-14Ch]-------------------产生的临时对象 的内存
010C6349  push        ecx------------------------------把临时对象的内存传进去
010C634A  call        test (010C1212h)
010C634F  add         esp,8
010C6352  mov         dword ptr [ebp-154h],eax
010C6358  mov         edx,dword ptr [ebp-154h]
010C635E  mov         dword ptr [ebp-158h],edx
010C6364  mov         byte ptr [ebp-4],2
010C6368  mov         eax,dword ptr [ebp-158h]
010C636E  push        eax
010C636F  lea         ecx,[a2]
010C6372  call        A::operator= (010C11B3h)
010C6377  mov         byte ptr [ebp-4],1
010C637B  lea         ecx,[ebp-14Ch]
010C6381  call        A::~A (010C128Fh)-------------------->在main函数中析构的
a3 = test2(a);
010C63BD  lea         eax,[a]
010C63C0  push        eax------------------------然而这，啥也没干
010C63C1  call        test2 (010C1235h)
010C63C6  add         esp,4
010C63C9  push        eax
010C63CA  lea         ecx,[a3]
010C63CD  call        A::operator= (010C11B3h)
*/