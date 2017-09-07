#include <iostream>
using namespace std;

class A
{
public:
	static A *getInstance()
	{
		/*会有线程安全问题*/
		if (!instance)
			instance = new A;
		return instance;
	}
	void show(){ cout << "东dong" << endl; }
private:
	static A *instance;
	A(){}
	~A(){}
};
A *A::instance = NULL;


int main()
{
	A *a = A::getInstance();
	a->show();

	system("pause");
	return 0;
}