#include <iostream>
using namespace std; 

//数组中除一个数字只出现1次外，其它数字都成对出现，要求尽快找出这个数字
//这么有规律肯定时间复杂度是O(N) 而且最好用位运算
int test1(int arr[],int len)
{
	int temp = 0;
	for(int i = 0;i<len;i++)
		temp ^= arr[i];
	return temp;
}

//如果是数组中有两个不同的数，其他的全是成对的
//思路：把不同的两个数分在不同的两个数组中，然后思路就和上面一样了
void FindTwoNum(int arr[],int len,int &num1,int &num2)
{
	//找到不同的两个数的^ 
	int temp = 0; 
	for(int i = 0;i<len;i++)
		temp ^= arr[i];
	//求出这两个数从二进制的哪一位开始不同的 (从前向后，从后向前都行，只要找出可以区分两个数字的点就好了)
	int i = 0;
	for(;i<sizeof(int) * 8;i++)
	 	if((temp >> i & 1) == 1)			// 注意 优先级  >> == &  一次降低    别写成了 (temp >> i) & 1 == 1 
	 		break;
	//现在就可以找出两个数了
	num1 = num2 = 0;
	for(int j = 0;j<len;j++)
		if((arr[j] >> i & 1)== 0)
			num1 ^= arr[j];
		else
			num2 ^= arr[j];
} 

int main()
{
//	int arr[] = {5,5,6,6,3,2,3,8,8};
//	cout<<test1(arr,sizeof(arr) / sizeof(arr[0]));
	int arr[] = {5,5,6,9,6,3,3,2,8,8};
	int a,b;
	FindTwoNum(arr,sizeof(arr) / sizeof(arr[0]),a,b);
	cout<<"a = "<<a<<"    "<<"b = "<<b<<endl;
}
