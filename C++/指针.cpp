#include<iostream>
#include<iomanip> 
using namespace std;
int main()
{
	int *p,a[3][3],i,j;
	for(i=0;i<3;i++)
	for(j=0;j<3;j++)
	{
	cin>>a[i][j];
	cout<<a[i][j];
}
	for(p=a[0];p<a[0]+9;p++)
	cout<<setw(4)<<*p;
	p=a[0];
	cout<<*(p+2)<<endl;
	cout<<*(*(a+1)+1);
} 
