#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	double s=1,sum=0,n=1,t=1;
	while(fabs(n)>1e-7)
	{
		sum=sum+n;
		s=-s;
		t=t+2;
		n=s/t;
	}
	cout<<"Ô²ÖÜÂÊÊÇ£º"; 
	cout<<sum*4<<endl;
	return 0;
}
