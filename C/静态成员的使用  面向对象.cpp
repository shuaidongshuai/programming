#include<iostream>
using namespace std; 
class dong
{
public:
	static void add(int a)
	{
		*p=a;
		p++;
	}
	static void print();
	static void sort();
	static int date[20];//声明静态内存空间
	static int *p;		//声明静态指针成员
};
int dong::date[20];   //实际定义，默认的初值为0
int *dong::p=date;	//实际定义，设初值为date数组的首地址
void dong::print()					//实现输入
{
	for(int i=0;i<(p-date);i++)
		cout<<date[i]<<",";
	cout<<endl;
}
void dong::sort()				//实现排序
{
	int n=p-date;
	for(int i=0;i<n;i++)
		for(int j=i+1;j<n;j++)
		if(date[i]>date[j])
		{
			int t=date[i];
			date[i]=date[j];
			date[j]=t;
		}
}
int main()
{
	int dong::date[20];
	int *dong::p=date;
	int n=p-date; 
	for(int i=0;i<n;i++)
	{
		cin>>a;
		dong::add(a);
	}
	dong::sort ();
	dong::print ();		//打印出已经排序好的数
	return 0;
}
