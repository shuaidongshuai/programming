#define  _CRT_SECURE_NO_WARNINGS
#pragma once
#pragma excution_character_set("utf-8")

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

class Student
{
public:
	string name;
	Student(string _name)
	{
		name = _name;
	}
	Student(const Student &s)
	{
		cout << "拷贝构造 我是："<<s.name << endl;
		//name = s.name;	//深拷贝
		
		name = s.name.c_str();//浅拷贝		//string.c_str是Borland封装的String类中的一个函数，它返回当前字符串的首字符地址。
	}
};
class Student2
{
public:
	char* name;
	Student2(char* _name)
	{
		name = _name;
	}
	Student2(const Student2 &s)
	{
		cout << "拷贝构造 我是：" << s.name << endl;

		name = s.name;//浅拷贝
	}
};



void test3()
{
	Student* s1 = new Student("陈明东");
	Student* s2 = new Student("马云");
	vector<Student*> v;
	v.push_back(s1);//直接传的地址进去（根本没有调用拷贝构造）(也可以说是浅拷贝)
	v.push_back(s2);

	for (vector<Student*>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << (*it)->name << "  ";
		if ((*it)->name == "马云")
		{
			(*it)->name = "马化腾";
		}
	}
	cout << endl;

	cout << s1->name << "  " << s2->name << endl;
}

void test2()
{
	Student s1("陈明东");
	Student s2("马云");
	Student s3("李彦宏");
	vector<Student> v;
	v.push_back(s1);//这里是深拷贝
	v.push_back(s2);
	v.push_back(s3);
	cout << "---------------------" << endl;
	for (vector<Student>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << (*it).name << "  ";
		if ((*it).name == "马云")
		{
			(*it).name = "马化腾";
		}
	}
	cout << endl;
	cout << s1.name << "  " << s2.name << "  " << s3.name << endl;

	//	拷贝构造 我是：陈明东
	//	拷贝构造 我是：陈明东
	//	拷贝构造 我是：马云				// 1
	//	拷贝构造 我是：陈明东
	//	拷贝构造 我是：马云
	//	拷贝构造 我是：李彦宏			// 2  从这两个地方可以看出来，用的是数组存储方式，每次加一个元素，其他元素都要移动，都要进行深拷贝
	//	----------------------
	//	陈明东  马云  李彦宏
	//	陈明东  马云  李彦宏
}

void test1()
{
	vector<int> v;
	for (int i = 0; i < 9; i++)
	{
		v.push_back(i);
	}
	v.push_back(5);
	v.push_back(5);
	v.push_back(6);

	//迭代器
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << "  ";
	}
	//算法
	int num1 = count(v.begin(), v.end(), 5);//求 5  的个数
	int num2 = count(v.begin(), v.end(), 6);//求 6  的个数
	cout << endl << "---------------------------" << endl;
	cout << "5的个数 = " << num1 << endl;
	cout << "6的个数 = " << num2 << endl;

}


