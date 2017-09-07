#include <iostream>
#include <vector>
using namespace std;

template<typename T>
void print(vector<T> &v)
{
	for (vector<T>::iterator it = v.begin(); it != v.end(); ++it)
		cout << *it << " ";
	cout << endl;
}

void test9()
{
	cout << "--------test9---------" << endl;
	vector<int> v;
	for (int i = 0; i<6; ++i)
		v.push_back(i);
	print(v);

	for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
	{
		/*
		if (*it == 3)
			v.erase(it); 
		
		当调用erase()后Iter迭代器就失效了，变成了一野指针。还加个P。★不过返回的是下一个元素的迭代器
		*/
	}

	//两种方法解决
	for (vector<int>::iterator it = v.begin(); it != v.end();)
	{
		if (*it == 3)
		{
			it = v.erase(it);//返回的是下一个元素的迭代器
			cout << "返回的是下一个元素 : " << *it << endl;
		}
		else
			++it;
	}
	print(v);
}