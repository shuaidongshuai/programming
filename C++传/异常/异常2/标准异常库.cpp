#include <iostream>
using namespace std;

class MyException :public exception//继承异常
{
public:
	MyException()
	{
		cout << "构造函数" << endl;
	}
	virtual const char *  what()
	{
		cout << "发生异常了" << endl;
		return NULL;
	}
};
void test5()
{
	throw MyException();
}
int main()
{
	try{
		test5();
	}
	catch (MyException m){
		m.what();
	}
	//	构造函数
	//	发生异常了
	system("pause");
}