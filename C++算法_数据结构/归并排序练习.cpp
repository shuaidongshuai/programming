#include <iostream>
#include <ctime>
#include <cstdlib> 
using namespace std;

void MergeArray(int *arr, int *temp, int left, int mid, int right){
	if(!arr || !temp || left > mid || mid > right){
		return;
	}
	int k = 0, l = left, r = mid + 1;//把mid算作左边的
	while(l <= mid && r <= right){
		if(arr[l] < arr[r]){
			temp[k++] = arr[l++];
		}else{
			temp[k++] = arr[r++];
		}
	}
	while(l <= mid){
		temp[k++] = arr[l++];
	}
	while(r <= right){
		temp[k++] = arr[r++];
	}
	for(int i = 0; i < k; ++i){
		arr[left + i] = temp[i];
	}
}
void SysMergeSort(int *arr, int *temp, int left, int right){
	if(left >= right){
		return;
	}
	int mid = (left + right) / 2;
	SysMergeSort(arr, temp, left, mid);
	SysMergeSort(arr, temp, mid + 1, right);
	MergeArray(arr, temp, left, mid, right);
}
void MergeSort(int *arr, int n){
	if(n <= 0 || !arr){
		return;
	}
	int *temp = new int[n];
	SysMergeSort(arr, temp, 0, n - 1);
}
int main(){
	int *arr = new int[10];
	srand(time(NULL));
	for(int i = 0; i < 10; ++i){
		arr[i] = rand()%100;
		cout<<arr[i]<<" ";
	}
	cout<<endl;
	MergeSort(arr, 10);
	for(int i = 0; i < 10; ++i){
		cout<<arr[i]<<" ";
	}
}
