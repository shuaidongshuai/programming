#include <iostream>
using namespace std;

class A{
public:
	int value;
	int max;
	char ch[10];
	int min;
	A(int x = 0) :value(x), max(x + 10), min(x + 20){}
	void fun(){ cout << "Afun" << endl; }
};
int main()
{
	cout << (int)&((A*)0)->value << endl;//强转0为（A*)类型
	cout << (int)&((A*)0)->max << endl;
	cout << (int)((A*)0)->ch << endl;
	cout << (int)&((A*)0)->min << endl;

	system("pause");
}
