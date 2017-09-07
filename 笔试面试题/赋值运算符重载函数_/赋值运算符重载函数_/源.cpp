#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vld.h>
using namespace std;

class Dong
{
private:
	char *str;
public:
	Dong(char *s)
	{
		str = new char[strlen(s) + 1];
		strcpy(str, s);
	}
	//1.返回值要返回*this的引用（可以连等）   2.传值用&在里面没有改变传进来的值（节省内存）
	Dong &operator =(const Dong &d)
	{
		//3.判断是否和自己相等
		if (this == &d) return *this;

		//4.delete自己指向的内存
		delete[] str;
		str = NULL;//避免野指针
		str = new char[strlen(d.str) + 1];
		strcpy(str, d.str);
		return *this;
	}
	~Dong()
	{
		delete[] str;
		str = NULL;
	}
};
//////////////////////上面4个方面已经很全面了，但是没有考虑到安全问题/////////////////////
/////////////////////////////new可能不成功抛出异常////////////////////////////////////////
class DongUP
{
private:
	char *str;
public:
	DongUP(char *s) 
	{
		str = new char[strlen(s) + 1];
		strcpy(str, s);
	}
	//与上面相比就是增加一个temp来存储原来的str，让str不会一开始就被delete
	DongUP &operator =(const DongUP &d)
	{
		if (this != &d)
		{
			//把要copy的内存放到tempStr中
			char *tempStr = new char[strlen(d.str) + 1];
			strcpy(tempStr, d.str);
			//交换tempStr和str的指针指向
			char *temp = tempStr;
			tempStr = str;
			str = temp;
			//释放原来str指向的内存
			delete[] tempStr;
		}
		return *this;
	}
	~DongUP()
	{
		delete[] str;
		str = NULL;
	}
};
int test2()
{
	DongUP d("chen");
	DongUP d2("shuaidong");
	DongUP d3("a");
	d3 = d2 = d;
	return 0;
}
int test1()
{
	Dong d("chen");
	Dong d2("shuaidong");
	Dong d3("a");
	d3 = d2 = d;
	return 0;
}
int main()
{
	test1();
	test2();
}