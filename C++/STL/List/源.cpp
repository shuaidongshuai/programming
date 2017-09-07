#include <iostream>
#include<algorithm>
#include <list>
using namespace std;

/* list 插入删除特别快 */

void print(list<int> l)
{
	for (list<int>::iterator it = l.begin(); it != l.end(); it++)
	{
		cout << *it << "\t";
	}
	cout << endl << "----------------------" << endl;
}

void test1()
{
	list<int> l;
	cout << l.size() << endl;

	for (int i = 0; i < 5; i++)
	{
		l.push_back(i);//尾插法
	}
	*l.begin() = 99;
	print(l);

	for (int i = 0; i < 5; i++)
	{
		l.push_front(i);//尾插法
	}
	print(l);

	list<int>::iterator it = l.begin();
	cout << *it << endl;
	it++;
	cout << *it << endl;
	//*it + = 5;  错误。不支持随机访问

	//插入
	l.insert(it, 1000);
	print(l);
	
	//删除区间
	l.erase(l.begin(), it);//注意 list 迭代器没有重载 +  所以l.begin() + 1 会报错
	print(l);

	l.erase(++l.begin());//删除第二个元素
	print(l);

	

}