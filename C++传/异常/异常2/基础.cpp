#include <iostream>
using namespace std;

class A{
public:
	int i;
	A(){
		cout << "构造函数" << endl;
		i = 0;
	}
	~A(){
		cout << "析构函数" << endl;
		i++;
	}
	A(const A &a)
	{
		cout << "拷贝构造函数" << endl;
	}
	void show()
	{
		cout << "show 函数" << endl;
		i++;
	}
};

void test()
{
	throw A();
}
void test2()
{
	throw new A;
}
void test3()
{
	throw &A();
}
//注意：*a可以和&a,a共存，但是&a和a不能共存
int main4()
{
	try{
		test3();
	}
	catch (A *a){			//所以这里是copy
		a->show();
		cout << a->i << endl;
		cout << "异常处理" << endl;
		//delete a;//这里调用delete程序会崩溃
	}
	//	构造函数
	//	析构函数
	//	show 函数		//这里还能说得过去，毕竟不占内存
	//	2				//这里真的很费解，为啥内存没有被释放★★★★★★★★★估计底层并不是简单的A* a = &A();
	//	异常处理
	system("pause");
	return 0;
}
int main3()
{
	try{
		test2();
	}
	catch (A *a){			//所以这里是copy
		a->show();
		cout << "异常处理" << endl;
		delete a;
	}
/*		构造函数
		show 函数
		异常处理
		析构函数	  注意需要自己调用delete函数才能被析构 */	
	system("pause");
	return 0;
}
int main2()
{
	try{
		test();
	}
	catch (A &a){			//所以这里是copy
		a.show();
		cout << "异常处理" << endl;
	}
	//	构造函数
	//	show 函数
	//	异常处理
	//	析构函数			//只调用了一次析构函数
	system("pause");
	return 0;
}
int main1()
{
	try{
		test();
	}
	catch (A a){			//所以这里是copy
		a.show();
		cout << "异常处理" << endl;
	}
	//	构造函数
	//	拷贝构造函数		//调用了拷贝构造
	//	show 函数
	//	异常处理
	//	析构函数			//两次析构
	//	析构函数
	system("pause");
	return 0;
}