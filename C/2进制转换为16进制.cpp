//二进制转化为16进制 
#include<iostream>
#include<string>
using namespace std;
string str;
int main()
{
	char str2;
	cin>>str;
	int a=str.length();
	if(a%4==1)
	str="000"+str;
	else if(a%4==2)
	str="00"+str;
	else if(a%4==3)
	str="0"+str;
	for(int i=0;i<a;i+=4)
	{
		str2=(str[i]-'0')*8+(str[i+1]-'0')*4+(str[i+2]-'0')*2+str[i+3];
		if(str2>57)
		str2+=7;														// 字符 9 =57  字符 A =65 
		cout<<str2;
	}
	return 0;
 } 
