#include<iostream>
using namespace std;
int main()
{
	int x,*p=&x;
	char a='B',*q=&a;
	cout<<hex<<p<<"  "<<p<<"  "<<&x<<endl; 
	cout<<hex<<p+3<<"  "<<p+3<<endl;
	cout<<hex<<q;
 } 
