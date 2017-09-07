#include <iostream>
using namespace std;

/*折半查找需要本身有序*/

#define ElemType int
/*递归*/
int search(ElemType *arr, int low, int hight, int key)
{
	if (low > hight || !arr)
		return -1;

	int mid = (hight + low) / 2;
	if (arr[mid] == key)
		return mid;

	if (arr[mid] > key)
		return search(arr, low, mid - 1, key);
	else
		return search(arr, mid + 1, hight, key);
}

/*非递归*/
int search2(ElemType *arr, int low, int hight, int key)
{
	int mid;
	while(low <= hight)
	{
		mid = (hight + low) / 2;
		if(arr[mid] == key)
			return mid;
		else if(arr[mid] > key)
			hight = mid - 1;
		else
			low = mid + 1;
	}
	return -1;
} 

int main()
{
	ElemType arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int in;
	cin>>in;
	cout << search(arr, 0, sizeof(arr) / sizeof(arr[0]) - 1, in) << endl;
	cout << search2(arr, 0, sizeof(arr) / sizeof(arr[0]) - 1, in) << endl;
}
