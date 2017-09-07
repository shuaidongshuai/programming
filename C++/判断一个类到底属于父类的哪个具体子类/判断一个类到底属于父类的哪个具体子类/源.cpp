#include <iostream>
using namespace std;
class B
{

};
class D1 : public B
{

};
class D2 : public B
{

};
void main1()
{
	B* b1 = new B;
	D1* b2 = new D1;
	D2* b3 = new D2;
	B* b4 = (B*)b2;//typeid 只能判断出是 B 类，，，，哎，，这种方法不行

	cout << (typeid(D1) == typeid(*b1)) << endl;//注意：typeid是操作符，不是函数！
	cout << (typeid(D1) == typeid(*b2)) << endl;
	cout << (typeid(D1) == typeid(*b3)) << endl;
	cout << (typeid(D1) == typeid(*b4)) << endl;

	cout << typeid(*b1).name() << endl;
	cout << typeid(*b2).name() << endl;
	cout << typeid(*b3).name() << endl;
	cout << typeid(*b4).name() << endl;

	cout << (typeid(D2) == typeid(*b1)) << endl;//注意：typeid是操作符，不是函数！
	cout << (typeid(D2) == typeid(*b2)) << endl;
	cout << (typeid(D2) == typeid(*b3)) << endl;
	cout << (typeid(D2) == typeid(*b4)) << endl;
	cin.get();
}