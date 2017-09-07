#include <iostream>
using namespace std;

void sort(int *arr,int n) 
{
	for(int i = 0;i < n;i++)
	{
		for(int j = i + 1;j < n;j++)
		{
			//从大到小,每次选出最大的 
			if(arr[i] < arr[j])
			{
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
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
	sort(arr,size);
	print(arr,size);
}
