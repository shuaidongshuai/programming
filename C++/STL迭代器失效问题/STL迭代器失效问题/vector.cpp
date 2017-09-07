#include <iostream>
#include <vector>
using namespace std;

void test(vector<int> &v)
{
	for (vector<int>::iterator it = v.begin(); it != v.end();)
	{
		if (*it % 2 == 0)
			it = v.erase(it);//这里不用++
		else
			it++;
	}
}
void test2(vector<int> &v)
{
	for (vector<int>::iterator it = v.begin(); it != v.end();)
	{
		if (*it % 3 == 0)
		{
			v.insert(it,10);//注意这里是在3的前面插入10   虽然迭代器不会失效，但是++it又变成了3 死循环，所以要++两次
			++it;
			++it;
		}
		else
			it++;
	}
	//上面代码的简写形式
	for (vector<int>::iterator it = v.begin(); it != v.end();++it)
	{
		if (*it % 3 == 0)
			v.insert(it++, 10);//注意这里是在3的前面插入10   虽然迭代器不会失效，但是++it又变成了3 死循环，所以要++两次
	}
}
void print(vector<int> &v)
{
	for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
		cout << *it << endl;
}
int main2()
{
	vector<int> v;

	for (int i = 0; i < 6; ++i)
		v.push_back(i);
	//for (int i = 0; i < 6; ++i)
	//	v[i] = i;//不能用角标，最开始没有内存，用角标会出现访问越界，但是如果分配了内存就能用了

	test(v);
	print(v);
	cout << "-------------------------" << endl;
	test2(v);
	print(v);

	system("pause");
	return 0;
}