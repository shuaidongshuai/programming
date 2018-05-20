#include <iostream>
using namespace std;

//数状数组
/* 修改 和 子数组和 时间复杂度都是log(n) */ 
class TreeArray{
private:
	int lowbit(int x){
	    return x&-x;
	}
	int *rawArr;
	int *treeArr;
	int n;
public:
	TreeArray(int *arr, int n):n(n){
		treeArr = new int[n]();
		rawArr = new int[n]();
		for(int i = 0; i < n; ++i)
			Updata(i, arr[i]);
	}
	~TreeArray(){
		delete[] rawArr;
		delete[] treeArr;
	} 
	void Updata(int idx, int val){
		//计算差值 
		int temp = val - rawArr[idx];
		rawArr[idx] = val;
		while(idx + 1 <= n){
			treeArr[idx] += temp;
			idx += lowbit(idx + 1); 
		}
	}
	//查询 0 -> k 子数组和 
	int Sum(int k){
		int ret = 0;
		while(k > 0){
			ret += treeArr[k];
			k -= lowbit(k + 1);
		}
		return ret;
	} 
	int Sum(int start, int end){
		return Sum(end) -  Sum(start - 1);
	}
	void PrintTree(){
		for(int i = 0; i < n; ++i)
			cout << treeArr[i] << " ";
		cout << endl;
	}
};
 
int main(){
	int arr[]{1, 5, 7, 2, 3, 8, 9, 7};
	TreeArray ta(arr, sizeof(arr) / sizeof(arr[0]));
	ta.PrintTree();	//	1 6 7 15 3 11 9 42
	cout << ta.Sum(4) << endl;	//	18
	cout << ta.Sum(1, 2) << endl;	//	13
} 
