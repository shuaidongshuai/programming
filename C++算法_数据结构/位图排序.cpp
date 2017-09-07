#include <iostream>
#include <bitset> 
#include <ctime>
#include <stdlib.h>
#define MAX 1000000

using namespace std;
//利用C++中的bitset 
//不过位图排序不能有相同的数 
void bitmapSort(int *arr,int len)
{
	bitset<MAX + 1> bitmap;			//声明一个有(MAX+1)个二进制位的bitset集合
	for(int i = 0;i<len;i++)
	{
		bitmap.set(arr[i]);
	}
	int j = 0;
	for(int i = 0;i<=MAX + 1;i++)
	{
		if(bitmap[i] == 1)
		{
			cout<<i<<"\t";
			if((j++ & 7) == 7)
				cout<<endl;
		}
	}
}

int main()
{
	int *arr = new int[MAX];
	srand((unsigned)time(NULL));
	for(int i = 0; i < 100; i++)
	{
		arr[i] = rand()%200;
		cout<<arr[i]<<"\t";
		if((i & 7) == 7)
			cout<<endl;
	}
	cout<<endl<<"-----------------------------------------------------"<<endl;
	
	bitmapSort(arr,100);
} 
