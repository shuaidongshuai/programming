#include <iostream>
using namespace std;
//求数组中出现次数超过一半的数字
//思路：
//		说明这个数字比其他所有数字加起来还多 

bool check(int *arr,int num,int len)
{
	int sum = 0;
	for(int i = 0;i<len;i++)
	{
		if(arr[i] == num)
			sum++;
	}
	return sum > len / 2;
}
int MoreThanHalfNum(int *arr,int len)
{
	if(!arr || len < 1) return 0;
	int times = 0;
	int num;
	for(int i = 0;i<len;i++)
	{
		if(0 == times)
		{
			num = arr[i];
			times = 1;
		}
		else
		{
			if(num == arr[i])
				times++;
			else
				times--;
		}
	}
	//用户不一定按套路出牌，万一没有那个大于一半的数呢 
	if(check(arr,num,len))
		return num;
	return 0;
}

int main()
{
	int arr[] = {1,2,3,3,2,2,4,2,2}; 
	cout<<MoreThanHalfNum(arr,9)<<endl;
}
