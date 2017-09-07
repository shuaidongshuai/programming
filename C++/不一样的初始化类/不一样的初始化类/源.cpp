#include <iostream>
using namespace std;

class A
{
	int i;
	char c;
public:
	A(){}
	A(int i, char c)
	{
		this->i = i;
		this->c = c;
	}

	void get()
	{
		cout << i << "   " << c << endl;
	}
};

int main()
{
	A a(1, 'd');
	a.get();

	A* b = new A(2, '2');
	b->get();

	cin.get();
}