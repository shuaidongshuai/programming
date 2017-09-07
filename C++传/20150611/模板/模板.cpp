#include<iostream>
using namespace std;

//1.调用的时候编译，不调用的时候不编译，，也就是说不调用的时候不会检查语法错误
//2.函数模板意义，通用，泛型
//3.原生函数优先于模板函数
//4.强行用模板 <>
template<class T>		//模板（template）
T add(T a, T b)
{
	cout << "调用T" << endl;
	return a + b;
}
double add(double a, double b)
{
	cout << "调用double" << endl;
	return a + b;
}
void main1()
{
	cout << add(1, 2) << endl;
	cout << add('1', '2') << endl;//返回值是一个char
	cout << '1' + '2' << endl;// ‘1‘的ascii码为 49  ’2‘为50   ’c‘为99
	cout << '1'<< endl;
	cout << '2' << endl;

	cin.get();
}
void main2()
{
	cout << add(1.0, 2.0) << endl;//原生函数优先于模板函数
	cout << add<double>(1, 2) << endl;//这样就可以调用摸板函数

	system("pause");
}