#include <iostream>
#include <windows.h>
#include <string>
using namespace std;
class Student3
{
public:
	string name;
	Student3(string _name)
	{
		name = _name;
	}
	Student3(const Student3 &s)
	{
		cout << "拷贝构造 我是：" << s.name << endl;
		//name = s.name;//浅拷贝
		name = s.getName();//一开始就想用这个，但是报错，因为const对象是不可以调用类中的非const成员函数
	}
	string getName() const//原来这里要加 const
	{
		return name;
	}
};