#include <iostream>
using namespace std;

class A
{
public:
	static A *instance;
	//static A *getInstance()//可以不要
	//{
	//	return instance;
	//}
	void show(){ cout << "东" << endl; }
private:
	A(){}
	~A(){}
};
A *A::instance = new A;


int main()
{
	A *a = A::instance;
	a->show();
	
	system("pause");
	return 0;
}