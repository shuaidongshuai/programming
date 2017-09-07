#include<iostream>
using namespace std;

constexpr int Dec(int i)
{
	return i - 1;
}
void main()
{
	//int a[5 + test()];
	int a = Dec(1);
	cout << a << endl;

	cin.get();
}