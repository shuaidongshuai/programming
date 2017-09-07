#include <iostream>
#include <set>
#include <vector>
#include <functional>
using namespace std;

//求数组中最小的k个数
//最好的解法是，开辟一个空间，这个空间只存放最小的k个数，但是每增加一个数就有可能对那片内存有所改动
//那片内存很容易想到的是用一个最大堆，但是短时间我们很难实现，所以如果面试官没有要求不能使用stl，我们可以用multiset集合，底层用的是红黑树 

//																这报错，vs中没问题 
void GetLeastNum(const vector<int>& data, multiset<int, greater<int>> &maxNum, int k)
{
	if (k < 1 || data.size() < k)
		return;
	maxNum.clear();
	for (vector<int>::const_iterator it = data.begin(); it != data.end(); it++)
	{
		if (maxNum.size() < k)
			maxNum.insert(*it);
		else
		{
			if (*it < *maxNum.begin())
			{
				maxNum.erase(maxNum.begin());
				maxNum.insert(*it);
			}
		}
	}

	for (multiset<int, greater<int>>::iterator it = maxNum.begin(); it != maxNum.end(); it++)
		cout << *it << " ";
	cout << endl;
}

int main()
{
	multiset<int, greater<int>> maxNum;
	vector<int> data;
	for (int i = 10; i >= 0; i--)
	{
		data.push_back(i);
	}
	GetLeastNum(data, maxNum, 4);
	getchar();
}
