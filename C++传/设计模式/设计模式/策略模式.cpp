#include<iostream>
using namespace std;

//抽象接口 
class Algorithm
{
public:
	virtual void replace() = 0;
};
//三种具体的替换算法 
class A_algorithm:public Algorithm{
public:
	void replace()
	{
		cout << "A_algorithm" << endl;
	}
};
class B_algorithm :public Algorithm{
public:
	void replace()
	{
		cout << "B_algorithm" << endl;
	}
};
class C_algorithm :public Algorithm{
public:
	void replace()
	{
		cout << "C_algorithm" << endl;
	}
};

//Cache需要用到替换算法 
class Cache
{
	Algorithm *a;
public:
	Cache(Algorithm *a)
	{
		this->a = a;
	}
	~Cache()
	{
		delete a;
	}
	void replace()
	{
		a->replace();
	}
};

enum al{ A, B, C }algorithm;
class Cache2
{
	Algorithm *a;
public:
	Cache2(enum al algor)
	{
		if (algor == A)
		{
			a = new A_algorithm;//自己new  不需要吧算法暴露出去，，和普通工厂模式差不多
		}
		else if (algor == B)
		{
			a = new B_algorithm;
		}
		else if (algor == C)
		{
			a = new C_algorithm;
		}
	}
	~Cache2() { delete a; }
	void replace()
	{
		a->replace();
	}
};

int main()
{
	//  如果用这种方式，客户就需要知道这些算法的具体定义。只能以下面这种方式使用，可以看到暴露了太多的细节。
	Cache(new B_algorithm()).replace();////暴露了算法的定义

	cout << "----------------" << endl;

	Cache2(C).replace();


	system("pause");
}