#include<iostream>
using namespace std;
int main()
{
	int s,n,t;
	for(s=0,t=1,n=1;n<=3;n++)
	t=t*n,s=s+t;
	cout<<s<<endl;
	return 0;
 } 
