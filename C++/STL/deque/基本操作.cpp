#include <iostream>
#include <deque>
#include<algorithm>
using namespace std;

void print(deque<int> d)
{
	for (deque<int>::iterator it = d.begin(); it != d.end(); it++)
	{
		cout << *it << "\t";
	}
	cout << endl << "----------------------" << endl;
}

//头插，尾插，删除
void test1()
{
	deque<int> d;
	d.push_back(1);
	d.push_back(2);
	d.push_back(3);

	d.push_front(7);
	d.push_front(8);
	d.push_front(9);

	print(d);

	cout << "头部元素：" << d.front() << endl;
	cout << "尾部元素：" << d.back() << endl;

	cout << "删除头部" << endl;
	d.pop_front();
	print(d);

	cout << "删除尾部" << endl;
	d.pop_back();
	print(d);

	//查找
	deque<int>::iterator it = find(d.begin(), d.end(), '2');
	int index = distance(d.begin(), it);//返回两个迭代器之间的位置
	cout << "2所在的位置：" << index << endl;
}