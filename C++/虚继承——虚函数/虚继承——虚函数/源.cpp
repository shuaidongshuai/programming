#include <iostream>
using namespace std;

class A{//虚基类

};
class B1 : virtual public A{						//有一个虚基指针，存储虚基类地址 
};
class B2 : virtual public A, virtual public B1{
};
class C1 : virtual public B2 ,virtual public A{		//一个虚基指针是4字节*3
};
class C2 : virtual public A{
	virtual void b1() = 0;//有一个vptr 指向了虚表的首地址
};
class C3 : virtual public A{
public:
	virtual void b1()
	{
		cout << "c3" << endl;
	}
};


int main()
{
	cout << "一个指针大小\t" << sizeof(int*) << endl;
	cout << "A\t" << sizeof(A) << endl;		// 1
	cout << "B1\t" << sizeof(B1) << endl;	// 4
	cout << "B2\t" << sizeof(B2) << endl;	// 8
	cout << "C1\t" << sizeof(C1) << endl;	// 12
	cout << "C2\t" << sizeof(C2) << endl;	// 8

	C1();
	//C2();		要注意含有纯虚函数的类，叫抽象类	抽象类不能实例化
	C3().b1();	//有虚函数的不是抽象类

	system("pause");
}