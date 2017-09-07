#include<iostream>
using namespace std;
template <class type>
type add(type a,type b)
{
	return a+b;
}
template <class type>			//不能删   这是重载函数模板 
type add(type a[],int n)
{
	type b=0;
	for(int i=0;i<n;i++)
	{
		b=a[i]+b;
	}
	return b;
}
int main()
{
	double a[]={1.5,2.5,5.2};
	 cout<<add(10,20)<<endl;
	 cout<<add(a,3)<<endl;
}
