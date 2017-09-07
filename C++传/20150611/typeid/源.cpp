#include<iostream>
using namespace std;
void main()
{
	int a;
	cout << typeid(a).name() << endl;
	cout << typeid(10).name() << endl;
	cout << typeid(19 + 1.1).name() << endl;
	cout << typeid("dong").name() << endl; 

	cin.get();
}