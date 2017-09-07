#include<iostream>
using namespace std;
int p1=2,p2=10;
int max(int a,int b)
{
	return a>b?a:b;
}
int dong(int L=1,int w=p1+p2,int h=max(p1,p2))
{
	return L*w*h;
}
int main()
{
	cout<<dong()<<endl;
	cout<<dong(5)<<endl;
	cout<<dong(5,10)<<endl;
	cout<<dong(5,10,15)<<endl;
	return 0;
}
