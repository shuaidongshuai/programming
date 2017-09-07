#include<iostream>
using namespace std;

void main1()
{
	//数组的两种初始化
	int a[5]{1, 2, 3, 4, 5};
	for (auto i : a)
	{
		cout << i << endl;
	}

	cout << endl;

	int *p(new int[5]{1, 2, 3, 4, 5});
	for (auto i : a)
	{
		cout << i << endl;
	}

	cin.get();
}

void main2()
{
	int a[5];
	for (int &i:a)
	{
		cin >> i;
	}
	for (auto i:a)
	{
		cout << i << endl;
	}

	system("pause");
}

