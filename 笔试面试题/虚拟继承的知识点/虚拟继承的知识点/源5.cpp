#include <iostream>
using namespace std;
class a
{
	int arr[20];
	virtual void test();
};
class b :public virtual a
{
	int bb;
};

void test6()
{
	cout << sizeof(a) << endl;
	cout << sizeof(b) << endl;
	cout << "-------------------------------------" << endl;
}

/*
84
92
*/