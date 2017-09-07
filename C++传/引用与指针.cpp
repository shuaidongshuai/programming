#include <iostream>
using namespace std;

void test1(int& t)
{
	t = 1000;
}
void test2(int *t)
{
	*t = 2000;
}
int main()
{
	int a = 10,b = 20;
	int *c;
	c = &a;

	
	test1(b);
	test2(c);
	
	cout<<a<<"   " <<b<<endl;
}
