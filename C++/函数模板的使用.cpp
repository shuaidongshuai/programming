#include<iostream>
#include<cstring>
using namespace std;
template<class type>			//定义一个函数模板 
void sort(type a[],int n)
{
	for(int i=0;i<n-1;i++)
	{
		for(int j=0;j<n-i-1;j++)
		{
			if(a[j]>a[j+1])
			{
				type ntmp=a[j];
				a[j]=a[j+1];
				a[j+1]=ntmp;
			}
		}
	}
}
int main()
{
	int a[]={85,95,45,76,75};
	sort(a,5);
	for(int i=0;i<5;i++)
	{
		cout<<a[i]<<endl;
	}
	double b[]={45.78,8.65,98.8,5.78,0.45,58.98};
	sort<double>(b,6);			//注意  这里要用  <double> 
		for(int j=0;j<6;j++)
		{
			cout<<b[j]<<endl;
		}
	return 0;
}
