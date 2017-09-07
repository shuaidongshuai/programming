#include <string>
#include <iostream>
using namespace std;
class Teacher
{
	int _age;
	string _name;
public:
	Teacher(){}
	Teacher(string name, int age)
	{
		_age = age;
		_name = name;
	}
	void show()
	{
		cout << "ÀÏÊ¦£º" << _name << "\tÄêÁä" << _age << endl;
	}
};

