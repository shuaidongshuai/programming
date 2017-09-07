#include<iostream>
using namespace std;


void main()
{
	int *p(new int(2));
	int *&pp = p;
	cout << *pp << "   " << *p << endl;

	const int *&ppp = (const int *&)p;
	cout << *ppp << "   " << *p << endl;
	*p = 120;
	cout << *ppp << "   " << *p << endl;


	cin.get();
}