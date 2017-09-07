#include <iostream>
#include <vector>
#include <string>
using namespace std;


void test4()
{
	vector<int> v(2);//初始化容量为10的数组  并赋值为0
	cout << v.size() << endl;

	v.push_back(9);
	v.push_back(10);

	cout << v.back() << endl;

	v.pop_back();

	cout << v.back() << endl;
	cout << v.front() << endl;
}

//初始化的几种方法
void test5()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	vector<int> v2 = v;
	for (int i = 0; i < 4; i++)
	{
		cout << v2[i] << endl;
	}

	cout << "------------" << endl;
	vector<int> v3(v);
	for (int i = 0; i < 4; i++)
	{
		cout << v3[i] << endl;
	}

	cout << "------------" << endl;
	vector<int> v4(v.begin() + 1, v.begin() + 3);//从1 开始  到 3前面 copy
	for (vector<int>::iterator it = v4.begin() ; it != v4.end(); it++)
	{
		cout << *it << endl;// 2 3
	}

	cout << "------------" << endl;
	vector<int> v5(5, 1);			//初始化容器容量为5  里面全部赋值为1
	for (int i = 0; i < 5; i++)
	{
		cout << v5[i] << endl;
	}
}
//可以不用每次都push进去
void test6()
{
	vector<int> v(10);
	for (int i = 9; i >= 0; i--)
	{
		v[i] = 10 - i;//这样赋值也是可以的。但是有个前提：容量必须够
	}

	v[5] = 1000;

	for (int i = 0; i < 10; i++)
	{
		cout << v[i] << endl;
	}

	cout << "--------------" << endl;
	//逆向迭代器
	for (vector<int>::reverse_iterator it = v.rbegin(); it != v.rend(); it++)
	{
		cout << *it << endl;
	}

	//迭代器
	//		1	2	3
	//      ▲					//v.begin()的位置
	//			    	▲		//v.end()的位置
	cout << "--------------" << endl;
	for (vector<int>::iterator it = v.end() - 1; it != v.begin(); it--)	//v.begin() - 1 会挂 ，所以这样反向输出需要在最后加上最开始的元素
	{
		cout << *it << endl;
	}
	cout << v.front() << endl;

}
//删除
void test7()
{
	vector<int> v(10);

	for (int i = 0; i < 10; i++)
	{
		v[i] = i;
	}
	v.push_back(5);

	
	//区间删除
	v.erase(v.begin() + 1, v.begin() + 3);//这样 元素  1 2 就被删除了

	//按位置删除
	v.erase(v.begin());//这样0 就被删除了


	cout << "--------------" << endl;
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << endl;
	}

	cout << "--------------" << endl;
	//删除指定的值
	for (vector<int>::iterator it = v.begin(); it != v.end(); )
	{
		if (*it == 5)
		{
			it = v.erase(it);//erase 返回一个迭代器。指向下一个位置。所以这里不能再it++了，不然会跳过一个元素不检查，而已如果这个元素在末尾，直接挂掉
		}
		else
		{
			it++;
		}
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << endl;
	}
}
//插入
void test8()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	//push只能插入到尾部，如果我们想在头部加元素，那么就是insert
	v.insert(v.begin(), 100);
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << endl;
	}
	cout << "--------------" << endl;

	//而且可以在任意位置插入
	v.insert(v.begin() + 2, 999);
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << endl;
	}
	cout << "--------------" << endl;
}