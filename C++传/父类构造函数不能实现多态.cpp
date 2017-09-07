#include <iostream>
using namespace std;

class A{
	public: 
	A(){
		cout<<"a"<<endl;
		show(); 
	}
	virtual void show()
	{
		cout<<"基类"<<endl;
	}
};

class B:public A{
	public: 
	B(){
		cout<<"b"<<endl;
	}
	void show()
	{
		cout<<"子类"<<endl;
	}
};

int main2()
{
	B b;
	b.show();
//	a
//	基类
//	b
//	子类
//1.调用父类的构造函数。。子类的vptr指针被初始化，指向父类的虚函数表
//2.当执行完毕父类构造函数，子类的vptr指针被重写赋值，指向子类的虚函数表 
}

//顺便证明了多态实现的三个条件。缺一不可 
int main()
{
	B b;
	cout<<"------------"<<endl; 
	A a = b;
	a.show(); //注意啊。。这里没有实现多态。。因为多态的三个条件之一，，“有父类指针（引用）指向子类对象 ”  没有满足 
	
	A* pa = &b;
	pa->show();//这里才是多态 
}
