#include <iostream>
using namespace std;

int c = 200;
class A
{
	int a;
public:
	static int b;
	void test1()
	{
		this->a = 10;
	}
	friend void test2()			// 一般声明在类中，实现在外面，在里面也行
	{
		//this->a = 20;				 注意1： 友元函数中没有this指针
		cout << A::b << endl;	//	 注意2： 就算访问类中静态成员也必须使用A::作用域   还有b不能private
		cout << c << endl;//全局可以访问
	}
};
int A::b = 20;

void test2();		//这里好像必须声明，那这样和题目正确答案就不符合了，答案没有test2（）声明照样可以

int main()
{
	test2();
	system("pause");
}