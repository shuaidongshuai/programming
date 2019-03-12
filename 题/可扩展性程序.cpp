#include <iostream>
using namespace std;
/*
输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有的奇数位于数组的前半部分，
所有的偶数位于位于数组的后半部分，并保证奇数和奇数，偶数和偶数之间的相对位置不变。

考官会问：如果是按正负分，或者%3==0 分呢？
那么就需要考虑程序的可拓展性 和 可重用性 
*/ 
void Reorder(int *arr,int len,bool func(int))
{
	if(!arr || len <= 0) return;
	int first = 0;
	int end = len - 1;
	while(first < end)
	{
		while(first < end && !func(arr[first]))
			first++;
		while(first < end && func(arr[end]))
			end--;
		if(first < end)
		{
			arr[first] += arr[end];
			arr[end] = arr[first] - arr[end];
			arr[first] = arr[first] - arr[end];
		}
	}
}
/*判断一个数是否是偶数*/ 
bool isEven(int n)
{
	return (n & 0x1) == 0; 
} 
/*判断一个数是否是能被3整除*/ 
bool is3(int n)
{
	return n % 3 == 0;
} 
/////////////////////////////////////////////////////
void test1()
{
//	int arr[] = {1,2,3,4,5,5,6,7,8};
//	int arr[] = {}; 
	int n = sizeof(arr) / sizeof(arr[0]);
	Reorder(arr,n,isEven);
	for(int i = 0;i<n;i++)
	{
		cout<<arr[i]<<" ";
	}
 } 
void test2()
{
	int arr[] = {3,1,4,5,6,7,8,9,10};
	int n = sizeof(arr) / sizeof(arr[0]);
	Reorder(arr,n,is3);
	for(int i = 0; i < n ;i++)
	{
		cout<<arr[i]<<" ";
	}
}
int main()
{
	test2();
}

