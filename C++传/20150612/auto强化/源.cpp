#include<iostream>
using namespace std;

int hello(int a, int b)
{
	return a + b;
}
auto dong(int a = 10, int  b = 10)->int(*)(int c, int d)
{
	//int(*   dong(int a, int  b)  )(int c, int d)
	cout << "a = " << a << "   " << "  b = " << b << endl;
	return hello;
}
int(*dong1(int a, int  b))(int c, int d)
{
	cout << "a = " << a << "   " << "  b = " << b << endl;
	return hello;
}
auto dong2(int a, int b)->auto(*)(int c, int d)->int(*)(int e, int f);

void main4()
{
	cout << (*dong())(9, 9) << endl;
	cout << (*dong1(4, 5))(9, 9) << endl;


	cin.get();
}

auto pf(void)->auto(*)(int x)->int(*)(int a, int b);
//auto pf(void)->         auto(*)(int x)->int(*)(int a, int b);
//auto pf(void)->         int(*   (*)(int x)    )(int a, int b)
//  int(*   (*   pf(void)      )(int x)    )(int a, int b)
void main3()
{
	cout << typeid(pf).name() << endl;//int (__cdecl*(__cdecl*__cdecl(void))(int))(int,int)
									//  int (       *(       *       (    ))(int))(int,int)
									//  int (       *(       *     pf(void))(int x))(int a, int b)
	cin.get();
}


auto (*f)() ->int(*)(){};
//上式等价于  
int(*  (*f1)()  )(){};

void main()
{
	cout << typeid(f).name() << endl;
	cout << typeid(f1).name() << endl;//int (__cdecl*(__cdecl*)(void) )(void)
									//int (         *(       *)(    ) )(    )

	cin.get();
}



auto add(int a, int b)->double//指明函数返回值为int  c++11  里面必须指明  好像C++14不用加->double
{
	return a + b;
}
void main1()
{
	cout << add(1, 4) << endl;//自动忽略  .00000
	printf("%f", add(1, 4));

	cin.get();
}