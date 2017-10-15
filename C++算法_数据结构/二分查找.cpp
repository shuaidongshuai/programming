#include <iostream>
#include <vector>
using namespace std;
//普通
int BinarySearch(vector<int> v, int key){
	int l = 0, r = v.size() - 1, mid;
	while (l <= r){
		mid = (l + r) / 2;
		if (key > v[mid]){
			l = mid + 1;
		}
		else if (key < v[mid]){
			r = mid - 1;
		}
		else{
			return mid;
		}
	}
	return -1;
}
//查找第一个比key大的元素(也是找相同key 最左边的那个)
int BinarySearch2(vector<int> v, int key){
	int l = 0, r = v.size() - 1, mid;
	while (l <= r){
		mid = (l + r) / 2;
		if (key > v[mid]){
			l = mid + 1;
		}
		else{
			r = mid - 1;
		}
	}
	if (l >= v.size()){
		l = -1;
	}
	return l;
}
int main() {
	int arr[] = { 1, 2, 3, 6, 6, 6, 7, 8, 9};
	int n = sizeof(arr) / sizeof(int);
	vector<int> v(arr, arr + n);
	cout << BinarySearch2(v, 4) << endl;
	system("pause");
}
