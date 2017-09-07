#include<iostream>
#include<string>
using namespace std;
int main()
{
	string str1,str2;
	str1="";
	str2=str1+"ming";
	cout<<str1<<endl;
	cout<<str2<<endl;
	str1="chen "+str2+" dong";
	cout<<str1<<endl;
	
	string a;
	a="0";
	a=a+1;
	cout<<a<<endl;
	a='1'+a;
	cout<<a<<endl;
	
	char b='6';
	cout<<"b="<<b<<endl;
	b=b+1;
	cout<<"b="<<b<<endl;
	b=b-5;
	cout<<"b="<<b<<endl;
} 
