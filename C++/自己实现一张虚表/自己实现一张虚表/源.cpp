#include<iostream>
using namespace std;

typedef void(*P)();


struct vtable{
	P p;
};
struct vtable v;
class A{
	v->p = void test()
	{
		cout << "A  test" << endl;
	}

};

class B : public A{

};

int main()
{



	system("pause");
}