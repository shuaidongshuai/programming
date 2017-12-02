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
//查找第一个比key大的元素(找相同key 最左边的那个)
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
//查找第一个比key大的元素(找相同key 最右边的那个)
int BinarySearch3(vector<int> v, int key){
	int l = 0, r = v.size() - 1, mid;
	while (l <= r){
		mid = (l + r) / 2;
		if (key >= v[mid]){
			l = mid + 1;
		}
		else{
			r = mid - 1;
		}
	}
	if (l >= v.size()){
		l = -1;
	}
	//return l - 1;//这里要 -1 ★★★★★★★上面是由于r-1才跳出循环的  下面是l+1才跳出循环的  所以需要 l - 1 
	return r;	//换成r也行 
}
int main() {
	int arr[] = { 0, 1, 2, 3, 6, 6, 6, 6, 7, 8, 9};
	int n = sizeof(arr) / sizeof(int);
	vector<int> v(arr, arr + n);
	for(int i = 0; i < n; ++i)
		cout<<i<<"->"<<arr[i]<<endl;
	cout << BinarySearch2(v, 6) << endl;
	cout << BinarySearch3(v, 6) << endl;
	system("pause");
}
