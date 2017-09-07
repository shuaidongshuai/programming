#define _CRT_SECURE_NO_WARNINGS
#include <cstddef> 
#include <fstream>
#include <iostream>
#include <vld.h>
using namespace std;

class Framis
{
public:
	int a;
	int b;
	static char *str;
	Framis():a(2),b(3){ cout << "构造\n"; }
	~Framis(){ cout << "析构"; }
	void* operator new(size_t size) throw(bad_alloc)
	{
		str = new char[10];
		strcpy(str, "hello");
		//char *a = new char[4];//必须是size，不然这个类的内存就不够，访问不会出问题，但是delete得时候你只new了4个字节，释放却释放了8个，会有问题
		char *a = new char[size];
		return a;//这里必须返回一个地址，不然这个类对象没有地址
	}
	void operator delete(void* f)
	{
		delete []str;
		delete f;
	}
};
char* Framis::str = NULL;
class A
{
};

int main()
{
	Framis *f = new Framis;
	cout << (void *)f << endl;
	cout << f->a << endl;
	cout << f->b << endl;
	delete f;
	return 0;
}