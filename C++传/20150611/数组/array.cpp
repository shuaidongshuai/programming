#include<iostream>
#include<array>
using namespace std;

void main()
{
	array<int, 2>myArr1{ { 1, 2 } };
	array<int, 2>myArr2{ 3, 4 };
	array<int, 2>myArr3{ 5, 6 };

	array<array<int, 2>, 3>myArr{ myArr1, myArr2, myArr3 };

	cout << typeid(myArr).name() << endl;

	for (auto j : myArr)
	{
		//cout << "j = " << typeid(j).name() << endl;
		for (auto i : j)
		{
	//		cout << "i = " << typeid(i).name() << endl;
			cout << i;
		}
		cout << endl;
	}

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 2; j++)
		{
			cout << myArr[i][j];
		}
		cout << endl;
	}

	cin.get();
}