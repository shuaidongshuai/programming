#include<iostream>
using namespace std;
int main()
{
	int a[2][3]={{1,2,3},{9,8,7}};
	int row=sizeof(a)/sizeof(a[0]);		//sizeof(a)表示整个数列占内存大小，，sizeof(a[0])表示一行元素所占内存 
	int column=sizeof(a[0])/sizeof(int);	//sizeof(int)表示得到一个Int元素的大小 
	cout<<row<<"\t"<<column<<endl;
 } 
