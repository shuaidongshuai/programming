#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	cout<<sizeof(short)<<endl;//2 
	cout<<sizeof(int)<<endl;//4
	cout<<sizeof(int*)<<endl;//指针占 8 个字节 
	cout<<sizeof(char)<<endl;//1
	cout<<sizeof(long)<<endl;//4
	cout<<sizeof(long long)<<endl;//8
	cout<<sizeof(float)<<endl;//4
	cout<<sizeof(double)<<endl;//8
	cout<<sizeof(long double)<<endl;//16
	//cout<<sizeof(long float)<<endl;//没有这种类型
}
