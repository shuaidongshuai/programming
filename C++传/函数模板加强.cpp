#include <iostream>
using namespace std;

template<class T1,class T2>//class和typename一样 
void mySwap(T1& a,T2& b)
{
	T1 c = a;
	a = b;
	b = c;
}

int main()
{
	int a = 48;//ascii码 对应 字符 0 
	char b = 'A';//ascii码 对应 数值 65 
	mySwap<int,char>(a,b);
	cout<<a<<"   "<<b<<endl;//65   0 
}
