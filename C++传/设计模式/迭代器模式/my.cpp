/*
迭代器模式（Iterator），提供一种方法顺序访问一个聚合对象中的各种元素，而又不暴露该对象的内部表示。
当你需要访问一个聚合对象，而且不管这些对象是什么都需要遍历的时候，就应该考虑使用迭代器模式。
另外，当需要对聚集有多种方式遍历时，可以考虑去使用迭代器模式。
迭代器模式为遍历不同的聚集结构提供如开始、下一个、是否结束、当前哪一项等统一的接口。
*/

#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;

template<class T>
class MyIterator
{
	T begin, end;
public:
	MyIterator(T t1,T t2)
	{
		begin = t1;
		end = t2;
	}
	bool hasNext()
	{
		if (begin != end)
			return true;
		return false;
	}
	T next()
	{
		T temp = begin++;
		return temp;
	}
};

int main()
{
	int a[] = { 1, 2, 3, 4, 5 };
	vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
	list<int> l(a, a + sizeof(a) / sizeof(a[0]));
	string str = "chen ming dong";
	
	//测试
	MyIterator<int*> *it = new MyIterator<int*>(a, a + sizeof(a) / sizeof(a[0]));
	while (it->hasNext())
	{
		int* i = it->next();
		cout << *i << endl;
	}
	delete it;
	cout << "---------------------------------" << endl;
	MyIterator<list<int>::iterator> *it2 = new MyIterator<list<int>::iterator>(l.begin(), l.end());
	while (it2->hasNext())
	{
		auto i = it2->next();
		cout << *i << endl;
	}
	cout << "---------------------------------" << endl;
	MyIterator<vector<int>::iterator> *it3 = new MyIterator<vector<int>::iterator>(v.begin(), v.end());
	while (it3->hasNext())
	{
		cout << *(it3->next()) << endl;
	}
	cout << "---------------------------------" << endl;
	MyIterator<string::iterator> *it4 = new MyIterator<string::iterator>(str.begin(), str.end());
	while (it4->hasNext())
	{
		cout << *(it4->next()) << endl;
	}
	cout << "---------------------------------" << endl;
	system("pause");
	return 0;
}
