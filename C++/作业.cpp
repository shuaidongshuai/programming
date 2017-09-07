#include <iostream>
#incluce <string>
using namespace std;

class Student
{
public:
	Student(int num,string name,string sex,string birth,int age,int math,int english,int pe)
	:num(num),name(name),sex(sex),birth(birth),age(age),math(math),english(english),pe(pe){}
	virtual void display() = 0;
protected:
	int num;
	string name;
	string sex;
	int math;
	int english;
	int pe;
	string birth;
	int age;
protected:
	void display_sys()
	{
		cout<<"学号:\t"<<num<<endl; 
		cout<<"姓名:\t"<<name<<endl;
		cout<<"性别:\t"<<sex<<endl;
		cout<<"生日:\t"<<birth<<endl;
		cout<<"年龄:\t"<<age<<endl;
		cout<<"数学成绩:\t"<<math<<endl;
		cout<<"英语成绩:\t"<<english<<endl;
		cout<<"体育成绩:\t"<<pe<<endl;
	}
};
class Undergraduate
{
public:
	Undergraduate(int num,string name,string sex,string birth,int age,int math,int english,int pe,string direction)
	:num(num),name(name),sex(sex),birth(birth),age(age),math(math),english(english),pe(pe),major(major){}
public:
	string major;
	void display()
	{
		display_sys();
		cout<<"专业:\t"<<major<<endl;
	}
};
class Graduate
{
public:
	Graduate(int num,string name,string sex,string birth,int age,int math,int english,int pe,string direction)
	:num(num),name(name),sex(sex),birth(birth),age(age),math(math),english(english),pe(pe),direction(direction){}
	void dispaly()
	{
		display_sys();
		cout<<"研究方向:\t"<<direction<<endl;
	}
private:
	string direction;
};

int main()
{
	
}
