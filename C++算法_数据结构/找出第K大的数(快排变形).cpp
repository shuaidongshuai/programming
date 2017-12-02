#include <iostream>
#include <vector> 
#include <algorithm>
#include <functional>
#include <cstdlib>
using namespace std;
/* 找出第 K 大的数*/
template<typename T>
T partition(vector<T> &v, int left, int right)/*从大到小排序  如果要求倒数第K个大的数，就从小到大好一点*/
{
	T t = v[left];
	while (left < right)
	{
		while (left < right && t > v[right])
			right--;
		v[left] = v[right];
		while (left < right && t <= v[left])
			left++;
		v[right] = v[left];
	}
	v[left] = t;
	return left;
}
/*在left - right 区间内第k大的数*/
template<typename T>
T search_K(vector<T> &v, int left, int right, int k)
{
	if (k == 0 && left == right)
		return v[left];
	int pos = partition(v, left, right);//pos这个位置不会再被移动
	int curK = pos - left + 1;//当前这个区间第curK大的数   + 1是因为数组是从0下标开始的
	if (curK > k)
		return search_K(v, left, pos - 1, k);
	else if (curK < k)
		return search_K(v, pos + 1, right, k - curK);
	return v[pos];
}
template<typename T>
T search_K(vector<T> v, int n, int k)
{
	return search_K<int>(v, 0, n - 1, k);
}

int main()
{
	vector<int> v;
	int n = 20;
	for (int i = 0; i<n; ++i)
	{
		v.push_back(rand() % 100);
		cout << v[i] << " ";
	}
	cout << endl;

	for (int i = 1; i <= n; ++i)
		cout << "第" << i << " 大的数:" << search_K<int>(v, n, i) << endl;

	sort(v.begin(), v.end(),greater<int>());
	for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
		cout << *it << " ";
	cout << endl;

	return 0;
}
