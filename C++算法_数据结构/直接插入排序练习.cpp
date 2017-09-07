#include <iostream>
using namespace std;

void insert(int *arr,int size)
{
	int temp;
	int j;
	for(int i = 1;i<size; i++)
	{
		temp = arr[i]; 
		//要把 temp 放到 前 i 个 中属于他的位置上 
		for(j = i - 1; j>= 0; j--)
		{
			if(temp < arr[j])
				arr[j + 1] = arr[j];
			else if(temp >= arr[j])
				break;
		}
		arr[j + 1] = temp;
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
	insert(arr,size);
	print(arr,size);
}
