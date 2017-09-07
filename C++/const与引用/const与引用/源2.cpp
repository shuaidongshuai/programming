#include<iostream>
using namespace std;

class A{
	int a, b, c;//12¸ö×Ö½ÚÁË
public:
	A(int a, int b, int c) :a(a), b(b), c(c)
	{

	}
};

A* test5()
{
	A* a = new A(1, 2, 3);
	return a;
}

int main55()
{
	A* aa;
	aa = test5();

	return 0;
}