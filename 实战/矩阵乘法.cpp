#include<iostream>
#include<iomanip> 
using namespace std;
int main()
{
	int i,j,k,a[2][3]={3,2,-1,2,-3,5},b[3][2]={1,3,-5,4,3,6},c[2][2];
	for(i=0;i<2;i++)
	{
		for(j=0;j<2;j++)
		{
			c[i][j]=0;
			for(k=0;k<3;k++)
			c[i][j]+=a[i][k]*b[k][j];
		}
	}
	for(i=0;i<2;i++)
	{
		for(j=0;j<2;j++)
		cout<<setw(3)<<c[i][j];
		cout<<endl;
	}
}
