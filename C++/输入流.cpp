#include<iostream>
using namespace std;
int main()
{
	cout<<"请输入一个字符(注意是一个字符)"<<endl;
	cout<<cin.get()<<endl;			//用 cin.get不会提取换行符 
	cin.get();						//用于清除上一行字符串的回车键
	
	char a;
	cout<<"再输入一个字符"<<endl; 
	a=cin.get();
	cout<<a<<endl;
	cin.get();
	
	cout<<"请输入一行字符串"<<endl;
	char s[20],p[20];
	cin.get(s,20);
	cout<<s<<endl;
	cin.get();						//用于清除上一行字符串的回车键
	
	cout<<"请输入一行字符串"<<endl;
	cin.getline(p,20);				//cin.getline会输出换行符
	cout<<p<<endl;
	
	return 0;
}
