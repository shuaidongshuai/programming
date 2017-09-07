#include <iostream>
using namespace std;
/* 书上的写法 */
void findGreatesSumOfSubArray(int *arr,int len)
{
	if(!arr || len < 1)
		return;
	int max = 0x80000000,sum = 0;
	for (int i = 0; i < len; ++i)
	{
		if(sum <= 0)
			sum = arr[i];
		else
			sum += arr[i];
		if(sum > max)
			max = sum;
	}
	cout<<max<<endl;
}
/* 自己的写法，感觉还是没有书上的好看 */
void findGreatesSumOfSubArray2(int *arr,int len)
{
	if(!arr || len < 1)
		return;
	int max = 0x80000000,sum = 0;
	for (int i = 0; i < len; ++i)
	{
		sum += arr[i];
		if(sum > max)
			max = sum;
		if(sum < 0)
			sum = arr[i++ + 1];
	}
	cout<<max<<endl;
}
/* 心情好，把带下标的也写了*/
void findGreatesSumOfSubArray3(int *arr,int len)
{
	if(!arr || len < 1)	
		return;
	int max = 0x80000000,sum = 0;
	int f,e,first = 0,end = 0;
	for(int i = 0; i < len; ++i)
	{
		if(sum <= 0)
		{
			sum = arr[i];
			first = i;
		}
		else
		{
			sum += arr[i];
			end = i;
		}
		if(sum > max)
		{
			max = sum;
			f = first;
			e = end;
		}
	}
	cout<<"最大子串和为："<<max<<endl;
	for(int i = f; i <= e; ++i)
		cout<<arr[i]<<" ";
	cout<<endl;
}
int main(int argc, char const *argv[])
{
	int arr[] = {1,-2,3,10,-4,7,2,-5};
	int n = sizeof(arr) / sizeof(n);
	findGreatesSumOfSubArray(arr,n);
	findGreatesSumOfSubArray2(arr,n);
	findGreatesSumOfSubArray3(arr,n);
	return 0;
}
