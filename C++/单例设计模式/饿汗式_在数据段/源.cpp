#include <iostream>
using namespace std;

/*在堆上*/
class A
{
public:
	static A *getInstance()
	{
		static A *instance = new A;
		return instance;
	}

	void show(){ cout << "东" << endl; }
private:
	~A(){ cout << "析构" << endl; }
	A(){ cout << "gouzhao" << endl; }
};
/*在数据段  在vs上程序结束有时候会崩溃*/
class A2
{
public:
	static A2 &getInstance()
	{
		static A2 instance;
		cout << (void *)&instance << endl;
		return instance;
	}
	void show(){ cout << "东" << endl; }
	//~A2(){ cout << "析构" << endl; }//析构函数必须共有
private:
	A2(){ cout << "gouzhao" << endl; }
};

int main1()
{
	A *a = A::getInstance();
	a->show();

	system("pause");
	return 0;
}
int main()
{
	A2 a = A2::getInstance();
	a.show();

	system("pause");
	return 0;
}