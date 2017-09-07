#include<iostream>
using namespace std;

void main5()
{
	auto fun = [](double a, double b){return a + b; };
	cout << fun(10, 10.2) << endl;
	//								指定返回类型
	auto fun2 = [](double a, double b)->int {return a + b; };
	cout << fun2(10, 10.2) << endl;



	cin.get();
}

void main4()
{
	//第一个()代表参数列表、、{}函数体、、、()调用
	[](char *s, int i){cout << "hello" << "   " << s << "   " << i << endl; }("dong", 20);

	cin.get();
}

void main3()
{
	[]{cout << "hello" << endl; cout << "dong" << endl; }();//匿名lambda表达式

	cin.get();
}

void main2()
{
	//分开写
	auto fun = [] {cout << "hello" << endl; };//函数指针
	fun();//调用函数
	cout << typeid(fun).name() << endl;//class <lambda_95d5bca3f836d50802ccb5cfb5d40759>

	cin.get();
}

void main1()
{
	[]{cout << "hello" << endl; }();

	cin.get();
}