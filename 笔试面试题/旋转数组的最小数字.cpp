/*
题目：把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。输入一个递增排序的数组的一个旋转，输出旋转数组的最小元素。
例如数组{3，4，5，1，2}为{1，2，3，4，5}的一个旋转，该数组的最小值为1。
可以使用二分查找法,时间复杂度O(logN)。
*/

#include <iostream>
using namespace std;

int MidOn(int *arr, int first, int end)
{
	int min = arr[first];
	for (int i = first + 1; i<end; i++)
	{
		if (min > arr[first])
			min = arr[first];
	}
	return arr[min];
}

int Min(int arr[], int len)
{
	//	if(!arr || len <= 0)
	//		throw new std::exception("Invaild parameters");	//例外

	int first = 0;
	int end = len - 1;
	int mid = first;															// 所以这里我们mid = first，目的：处理没有旋转（旋转数是0）的情况 
	while (arr[first] >= arr[end])	//一般来说first >= end  除了没有旋转 这种情况 
	{
		if (first + 1 == end)
		{
			mid = end;
			break;
		}
		mid = (first + end) / 2;

		//当前后和中间的数都相等的情况下，只能遍历    例如 1 0 1 1 1  
		if (arr[first] == arr[end] && arr[first] == arr[mid])
			return MidOn(arr, first, end);

		if (arr[mid] >= arr[first])
			first = mid;
		else if (arr[mid] <= arr[end])
			end = mid;
	}
	return arr[mid];
}

int main()
{
	//int arr[] = { 4, 5, 6, 1, 2, 3 };
//	int arr[] = { 1, 2, 3, 4, 5, 6, };
	int arr[] = { 1, 0, 1, 1, 1 };
	cout << Min(arr, sizeof(arr) / sizeof(arr[0])) << endl;
}

