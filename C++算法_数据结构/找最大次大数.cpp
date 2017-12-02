#include <iostream>
#include <ctime>
#include <algorithm>
#include <functional>
using namespace std;

void FindMaxSecond(int *arr, int len){
	if(!arr || len <= 0)
		return;
	int max = arr[0];
	int second = 0x80000000;
	for(int i = 1; i < len; ++i){
		if(max < arr[i]){
			second = max;
			max = arr[i];
		}
		else if(second < arr[i])
			second = arr[i];
	}
	cout << "max : " << max << "  second : " << second << endl;
}

int main(){
	int arr[10];
	srand(time(NULL));
	for(int i = 0; i < 10; ++i){
		arr[i] = rand()%100;
		cout << arr[i] << " "; 
	}
	cout<<endl;
	FindMaxSecond(arr, sizeof(arr) / sizeof(arr[0]));
	sort(arr, arr + 10, greater<int>());
	for(int a : arr)
		cout<<a<<" ";
	cout<<endl;
}
