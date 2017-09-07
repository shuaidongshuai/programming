#include <iostream>
using namespace std;

void swap(int &a,int &b)
{
	a += b;
	b = a - b;
	a -= b;
}

void bubble(int *arr,int n)
{
	for(int i = 0;i < n - 1;i++)// i 代表次数 一共要进行 n - 1 次 
	{
		for(int j = 0;j < n - 1 - i ;j++)//每次都会选出最小的一个放到后面 
		{
			//从大到小 
			if(arr[j] < arr[j + 1])
				swap(arr[j],arr[j+1]);
		}
	}
}
void print(int *arr,int n)
{
	for(int i = 0;i < n;i++)
		cout<<*arr++<<" ";
	cout<<endl;
}

int main()
{
	int arr[] = {4,5,6,1,9,2,3,7,8,11,0};
	int size = sizeof(arr)/sizeof(arr[0]);
	bubble(arr,size);
	print(arr,size);
}
