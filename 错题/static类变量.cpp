#include <iostream>
using namespace std;
/*
static类变量是所有对象共有，其中一个对象将它值改变，其他对象得到的就是改变后的结果
*/ 
class A
{
public:
	static int i;	
};
int A::i = 1;

int main()
{
	A a;
	A a2;
	a.i++;
	a2.i++;
	cout<<a.i<<endl;
	cout<<a2.i<<endl;
}
