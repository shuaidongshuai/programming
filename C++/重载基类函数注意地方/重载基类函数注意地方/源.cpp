#include <iostream>
using namespace std;
/*
如果基类声明被重载了，则应该在派生类中重新定义所有的基类版本。
如果在派生类中只重新定义一个版本，其他版本将会被隐藏，派生类对象将无法使用它们。
*/
class A{
public:
	void test()
	{
		cout << "Atest" << endl;
	}
};

class B : public A{
public:
	void test(int i)			//重载了父类的test函数。。父类的test（）函数就被隐藏了 
	{
		cout << "Btest" << i << endl;
	}
};

class C{
public:
	void test(int i){
		cout << "Ctest1" << i << endl;
	}
	void test(){
		cout << "Ctest1" << endl;
	}
};
class D : public C{
public:
	void test(int i){					//只要就算不是重载父类的函数，只是重定义了父类的函数也会隐藏父类的几个重载函数
		//test();//错误，D类没有test
		C::test();//可以
		cout << "Dtest1" << i << endl;
	}
};
int main()
{
	//B().test();				//出错，，因为B中根本没有test的无参函数 
	B().A::test();				//但是我们可以指明调用父类的方法 
	D().test(100);

	system("pause");
}