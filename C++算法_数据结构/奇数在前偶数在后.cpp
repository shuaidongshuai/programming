#include <iostream>
using namespace std;

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}
void Order(int *arr, int len){
	if(!arr || len < 1)
		return;
	int *start = arr;
	int *end = start + len - 1;
	while(start < end){
		while(start < end && (*start & 1) == 1)//  注意：  装B记得加括号--优先级 
			++start;
		while(start < end && (*end & 1) == 0)
			--end;
		if(start < end)
			swap(start, end);
	}
}
///////////////////如果要求相对位置不变，并且不能用辅助空间//////////////////////////
void Order2(int *arr, int len) {
	if(!arr || len < 1)
		return;
	int left = 0, right = 0;//因为后面要挪位置，所以不用指针 
	while(right < len && (arr[right] & 1) == 0) 
		++right;
	while(right < len){
		if((arr[right] & 1) == 1){
			int temp = arr[right];
			for(int i = right - 1; i >= left; --i)
				arr[i + 1] = arr[i];
			arr[left++] = temp;
		}
		++right;
	}
}
 //////////////////////////测试//////////////////////////////
void print(int *arr, int len){
	for(int i = 0; i < len; ++i){
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}
void test1(){
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int len = sizeof(arr) / sizeof(arr[0]);
	print(arr, len);
	Order(arr, len);
	print(arr, len);
} 
void test2(){
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int len = sizeof(arr) / sizeof(arr[0]);
	Order2(arr, len);
	print(arr, len);
} 
int main(){
	test1();
	cout << "-----------相对位置不变--------------" << endl; 
	test2();
} 
