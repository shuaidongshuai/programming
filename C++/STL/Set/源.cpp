#include <iostream>
#include <functional>
#include <set>
using namespace std;

void test1()
{
	set<int> s;
	for (int i = 0; i < 5; i++)
	{
		s.insert(rand() % 100);
	}

	s.insert(88);//不能有重复的元素
	s.insert(88);
	s.insert(88);

	for (set<int>::iterator it = s.begin(); it != s.end(); it++)
	{
		cout << *it << "\t";
	}
	cout << endl;

	//删除元素
	set<int>::iterator it;
	while (!s.empty())
	{
		it = s.begin();
		cout << *it << "\t";
		s.erase(s.begin());
	}
	cout << endl;
}

//自定义大小
void test2()
{
	set<int> s;
	set<int, less<int>> s2;//前两种，等价
	set<int, greater<int>> s3;//从大到小排序
	for (int i = 0; i < 5; i++)
	{
		s3.insert(rand() % 100);
	}
	for (set<int>::iterator it = s3.begin(); it != s3.end(); it++)
	{
		cout << *it << "\t";
	}
	cout << endl;
}
