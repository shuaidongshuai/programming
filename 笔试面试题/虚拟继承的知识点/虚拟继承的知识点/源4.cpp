#include <iostream>
using namespace std;
class a
{
	int arr[20];
};
class b :public virtual a
{
	int bb;
};

void test5()
{
	cout << sizeof(a) << endl;
	cout << sizeof(b) << endl;
	cout << "-------------------------------------" << endl;
}

/*
80
88
*/