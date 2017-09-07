#include <iostream>
using namespace std;

class A{
	public:
		virtual void show()
		{
			cout<<"A"<<endl;
		}
};

class B:public A{
	//int i; 
	public:
	void show()
	{
		cout<<"B"<<endl;
	}
};

int main()
{
	B b[3] = {B(),B(),B()};//3个B类的  数组
	
	A* a = b; 
	B* bb = b;
	
	a->show();
	bb->show();
//	B 
//	B
	
	a++;
	bb++;
	//运行结果一样 
	a->show();
	bb->show();
	//不要以为没有问题了,,把B类中注释的//int i; 打开后，直接就崩溃了
	
	//因为 子类 大小一旦和 父类 不一样，，那么 a++ bb++就不一样了，，a++是加了基类大小  bb++是加了派生类大小 
	 
}
