#include <iostream>
using namespace std;

class A{
public:
	int value;
	static int num;
	int max;
	char ch[10];
	int min;
	A(int x = 0) :value(x), max(x + 10), min(x + 20){}
	void fun(){ cout << "Afun" << endl; }
};
int A::num = 0;

int main1()
{
	int *p = NULL;			//0x00000000
	int A:: *s = NULL;		//0xffffffff    为什么是这个数呢？ 猜：转化成有符号整形就是 -1 代表s还没有指向A（但是类型是A类型）所以是-1
	int *z;
	p = &A::num;			//0x013df320 在.data 段 本身就有地址
	s = &A::value;			//0x00000000	在value的起始地址处 这时候就处于A类型的0地址处
	
	cout << s << endl;//直接打印打印不出来（s上存的地址），因为他指向的是相对地址，并没有为他分配地址
	cout << (int )*(int **)&s << endl;//这一步做的就是把s上存的地址变成一个int类型，需要对s取地址
	s = &A::max;			//0x00000004	在max的起始地址处	这时候就处于A类型的4地址处
	cout << (int)*(int **)&s << endl;
	s = &A::min;			//0x00000014	在min的起始地质处	这时候value(4) + max(4) + ch(12) = 20 = 0x14
	cout << (int)*(int **)&s << endl;

	p += 1;
	//s += 1;			//错误：左操作数包含“int A::* ”类型    我猜： 编译器根本不知道 int A::*要跳多少字节，所以出错
	//void(A:: *ptr)() = &A::fun;	//在gcc中是不报错的
	system("pause");
	return 0;
}