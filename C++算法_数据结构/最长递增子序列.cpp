#include <iostream>
#include <vector>
using namespace std;

//时间O(n^2)
void MaxIncrSubStr(vector<int> v) {
	if (v.empty()){
		return;
	}
	int n = v.size();
	int *res = new int[n]();//str[i]结尾的最长递增子序列 元素个数为res[i]
	res[0] = 1;
	int cur_max;
	int all_max = 1;
	for (int i = 1; i < n; ++i) {
		cur_max = 1;
		for (int j = 0; j < i; ++j) {
			if (v[i] > v[j] && cur_max < res[j] + 1){
				cur_max = res[j] + 1;
			}
		}
		res[i] = cur_max;
		if (all_max < cur_max){
			all_max = cur_max;
		}
	}
	cout << all_max << endl;
}
//时间O(N * logN)
void MaxIncrSubStr2(vector<int> v) {
	if (v.empty()){
		return;
	}
	int n = v.size();
	int *res = new int[n]();//元素个数为 i + 1 的子序列 最小末尾数为res[i]
	res[0] = v[0];
	int idx = 0, mid, l, r;
	for (int i = 1; i < n; ++i) {
		//2分查找(logN) 从左至右第一个比v[i]大的数 并替换它
		l = 0;
		r = idx;
		while (l <= r){
			mid = (l + r) / 2;
			if (v[i] > res[mid]){
				l = mid + 1;
			}
			else {
				r = mid - 1;
			}
		}
		if (l > idx){
			++idx;
		}
		res[l] = v[i];
	}

	cout << idx + 1 << endl;
	/////////////第二种方法时间复杂度小 而且容易打印////////////////
	for (int i = 0; i < idx + 1; ++i){
		cout << res[i] << " ";
	}
	cout << endl;
}
int main() {
	int arr[] = { 203, 39, 186, 207, 83, 80, 89, 237, 247 };
	int n = sizeof(arr) / sizeof(int);
	vector<int> v(arr, arr + n);
	MaxIncrSubStr(v);
	MaxIncrSubStr2(v);
	system("pause");
}

/*
https://www.nowcoder.com/questionTerminal/585d46a1447b4064b749f08c2ab9ce66
测试用例:
[203,39,186,207,83,80,89,237,247],9
对应输出应该为:
5
*/