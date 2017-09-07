#include<iostream>
using namespace std;
int main()
{
	int i,a[5];
	for(i=0;i<5;i++) cin>>a[i];			//scanf这样做就不可以 
	for(i=4;i>=0;i--) cout<<a[i]<<endl;
}
