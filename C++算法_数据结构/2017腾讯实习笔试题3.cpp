/*
小Q今天在上厕所时想到了这个问题：有n个数，两两组成二元组，差最小的有多少对呢？差最大呢？
输入描述:
 输入包含多组测试数据。
 对于每组测试数据：
 N - 本组测试数据有n个数
 a1,a2...an - 需要计算的数据
 保证:
 1<=N<=100000,0<=ai<=INT_MAX.
输出描述:
对于每组数据，输出两个数，第一个数表示差最小的对数，第二个数表示差最大的对数。
输入例子1:
6
45 12 45 32 5 6
输出例子1:
1 2

1.先排序
     特殊情况：如果排完序之后发现数组中所有数都相同，直接输出结果
         结果为：差最大个数 = 差最小个数 = （n * (n-1))/2;(两两组合)
2.统计数组中每种数字的个数（这里用的map）
3.计算差最小个数
    3.1.如果数组中没有重复数字，说明最小差不为0，最小差肯定是数组中相邻两个数的差
        因此，遍历一边数组，计算并统计最小差。
    3.2.如果数组中有重复数字，说明最小差是0，此时，遍历一边map，数字个数不为0的
        数字会产生最小差0，利用公式计算即可
4.计算差最大个数
    只有一种情况，最大值与最小值的两两组合，即最大值个数 * 最小值个数
算法复杂度：排序O(nlogn), 统计O(n)
*/
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

void CountMin(vector<int> &v){
	if(v.empty())
		return;
	int count = 0, size = v.size();
	map<int, int> m;
	bool flag = false;
	for(int i = 0; i < size; ++i){
		auto it = m.find(v[i]);
		if(it == m.end()){
			m.insert(make_pair(v[i], 1));
		}
		else{
			++m[v[i]];
			flag = true; 
		}
	}
	if(flag){
		int num;
		for(auto it = m.begin(); it != m.end(); ++it){
			num = it->second;
			count += num * (num - 1) / 2;
		}
	}
	else{
		int min = 0x7fffffff;
		for(int i = 1; i < size; ++i){
			if(v[i] - v[i - 1] == min)
				count++;
			else if(v[i] - v[i - 1] < min){
				min = v[i] - v[i - 1];
				count = 1;
			}
		}
	}
	cout << count << " ";
}
void CountMax(vector<int> &v){
	if(v.empty())
		return;
	int min = v[0], minCount = 0;
	for(auto it = v.begin(); it != v.end(); ++it){
		if(min == *it)
			++minCount;
		else
			break;
	}
	int max = *v.rbegin(), maxCount = 0;
	for(auto it = v.rbegin(); it != v.rend(); ++it){
		if(max == *it)
			++maxCount;
		else
			break;
	}
	cout << minCount * maxCount << endl;
}
void Count(vector<int> v){
	if(v.empty())
		return;
	sort(v.begin(), v.end());
	int size = v.size();
	if(v[0] == v[size - 1]){
		int count = size * (size - 1) / 2;
		cout << count << " " << count << endl; 
	}
	else{
		CountMin(v);
		CountMax(v);
	}
}
int main(){
	int n;
	while(cin >> n){
		vector<int> v;
		int num;
		while(n-- > 0){
			cin >> num;
			v.push_back(num);
		}
		Count(v);
	}
} 

