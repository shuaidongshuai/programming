#include<iostream>
#include<cstring>
using namespace std;
class dong1
{
public:
	dong1()
	{
		cout<<"调用dong构造函数"<<endl;
	}
	void set(char *p)
	{
		strncpy(name,p,sizeof(name));
	}
	char *get()
	{
		return name;
	}
	char name[20];
	~dong1()
	{
		cout<<"调用dong析构函数"<<endl;
	}
};
class cat:public dong1
{
public:
	cat()
	{
		cout<<"调用cat构造函数"<<endl;
	}
	~cat()
	{
		cout<<"调用cat析构函数"<<endl;
	}
	void dis()
	{
		cout<<"猫的名字："<<get()<<endl;
	}
};
int main()
{
	cat a;
	a.set ("dong");
	a.dis();
	a.set("chen");
	a.dis();
	return 0;
}


