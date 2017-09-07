#include <iostream>
using namespace std;

class A{
public:
	int i;
	A(){
		cout << "构造函数" << endl;
		i = 0;
	}
	~A(){
		cout << "析构函数" << endl;
		i++;
	}
	A(const A &a)
	{
		cout << "拷贝构造函数" << endl;
	}
	void show()
	{
		cout << "show 函数" << endl;
		i++;
	}
};
A* test()
{
	return &A();
}
int main5()
{
	A* a = test();
	a->show();
	cout << a->i << endl;
	//	构造函数
	//	析构函数
	//	show 函数		函数不占类的内存，所以我们还能调用，只要有这个类的对象名
	//	- 858993459		内存被释放，导致i变成了垃圾值
	system("pause");
	return 0;
}