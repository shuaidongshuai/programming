#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

void test1()
{
	int a[] = { 1, 34, 3, 5, 34, 32, 54, 32, 5 };
	for (auto i : a)
	{
		cout << i << " ";
	}
	cout << endl;
}
void test2()
{
	std::map<std::string, std::vector<int>> map;
	std::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	map["one"] = v;
	for (const auto& kvp : map)
	{
		std::cout << kvp.first << std::endl;
		for (auto v : kvp.second)
		{
			std::cout << v << std::endl;
		}
	}
}
void test3()
{
	int arr[] = { 1, 2, 3, 4, 5 };
	for (int& e : arr)
	{
		e = e*e;
	}
	for (auto i : arr)
	{
		cout << i << " ";
	}
	cout << endl;
}
int main()
{
	test1();
	test2();
	test3();
	system("pause");
}