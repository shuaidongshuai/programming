#include <iostream>
using namespace std;

/* 方法一 用单例  缺点：全局只能有一个，而且必须在堆上*/
class AA
{
public:
	AA *getInstance(){ return instance; }
private:
	static AA *instance;
	AA(){}
	~AA(){}
};
AA *AA::instance = new AA;

/* 方法二  利用继承、模板、 友元  优点：可以有多个实例，也可以在栈上*/
template<typename T>
class A
{
	friend T;
public:
	A(){}
	~A(){}
};
/* B就是不能被继承的类  继承B的类肯定要调用A的构造函数，但是只有B是A的友元函数 */
class B:public A<B>
{
public:
	B(){}
	~B(){}
};

int main()
{
	B b;
	B b2;
}
