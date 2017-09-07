#include <iostream>
using namespace std;

int main()
{
	int *arr = new int[20];				//这里只是申请了空间，里面的值是随机的，没有初始化的 
	for(int i = 0 ;i<20;i++)
	{
		if(i%5 == 0)
			cout<<endl;
		cout<<arr[i]<<"\t";
	}
	cout<<endl<<"-------------------------------------------"<<endl;
	int *array = new int[20]();			//这里不仅申请了空间，里面的值还全部初始化为0了 
	for(int i = 0 ;i<20;i++)
	{
		if(i%5 == 0)
			cout<<endl;
		cout<<array[i]<<"\t";
	}
	
}
