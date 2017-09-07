#include <iostream>
using namespace std;

class A{
	public: //没有public 的构造函数，，就不能被别人继承，，因为别人继承的构造函数里必须 
	A(){
		cout<<"a"<<endl;
	}
};

class B:public A{
	public://没有public 的构造函数，就不能创建对象。不算单例 
	B(){
		cout<<"b"<<endl;
	}
};

int main()
{
	B b;
	//a
	//b
	//先调用父类构造 
}
