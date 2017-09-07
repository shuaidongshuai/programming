#include<iostream>
#include<array>
using namespace std;
//模板别名，用别名优化模板的名称，类，命名空间， 全局，不可以放到函数内部
template<class T> using t = array <T, 6>;
template<class T,size_t n> using t2 = array <T, n>;

void main()
{

	t<int> arr = { 1, 2, 3, 4, 5, 6 };
	for (int i : arr)
	{
		cout << i;
	}
	cout << endl;
	t2<int, 10> arr2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	for (int i : arr2)
	{
		cout << i;
	}
	cin.get();
}


void main1()
{
	int arr1[6]{1, 2, 3, 4, 5, 6};
	array<int, 6> arr2{ { 1, 2, 3, 4, 5, 6 } };
	array<int, 6> arr3 = { 1, 2, 3, 4, 5, 6 };

	for (int i : arr1)
	{
		cout << i;
	}
	cout << endl;
	for (int i : arr2)
	{
		cout << i;
	}
	cout << endl;	for (int i : arr3)
	{
		cout << i;
	}
	cout << endl;

	cin.get();
}