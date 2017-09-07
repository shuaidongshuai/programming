#include <iostream>
#include <cstring>
using namespace std;
//num十进制转化为n进制 
void ToN(int num,int n)
{
	char arr[32];
	memset(arr,0,sizeof(arr));
	int temp,j = 31;
	while(num)
	{
		arr[j] = num % n;
		if(arr[j] <= 9)
			arr[j] += '0';
		else if(arr[j] > 9 && arr[j] < 36)
			arr[j] += 'A' - 10;
		else
		{
			cout<<"有错误"<<endl;
			return;
		}
		j--;
		num /= n;
	}
	while(++j < 32)
		cout<<arr[j];
	cout<<endl;
}

int main()
{
	int num,n;
	while(1)
	{
		cin>>num>>n;
		ToN(num,n);
	}
} 
