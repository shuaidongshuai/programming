#include <iostream>
#include <queue>
#include<functional>
using namespace std;

//struct less : public binary_function<int, int, bool>
//{	
//	bool operator()(const int& _Left, const int& _Right) const// functor for operator<
//	{	
//		return (_Left < _Right);// apply operator< to operands
//	}
//};

void test1()
{
	priority_queue<int> p;	//默认最大值优先
	//和下面这样写  是等价的
	priority_queue<int, vector<int>, less<int>> p2;//less是一个函数，底层封装好了
	priority_queue<int, vector<int>, greater<int>> p3;//需要functional头文件
	for (int i = 0; i < 5; i++)
	{
		p.push(rand() % 100);
		p2.push(rand() % 100);
		p3.push(rand() % 100);
	}

	cout << "队头元素：" << p.top() << endl;

	cout << "+++++++++++++++都是从大到小排序+++++++++++++++ " << endl;
	while (p.size() > 0)
	{
		cout << p.top() << "\t";
		p.pop();
	}
	cout << endl << "----------------------" << endl;
	while (p2.size() > 0)
	{
		cout << p2.top() << "\t";
		p2.pop();
	}

	cout << endl << "-------------测试从小到大排序-------------" << endl;
	while (p3.size() > 0)
	{
		cout << p3.top() << "\t";
		p3.pop();
	}
	cout << endl;

}

int main()
{
	test1();
	system("pause");
}
