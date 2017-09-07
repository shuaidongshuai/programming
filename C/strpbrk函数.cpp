#include <iostream>
#include <cstring> 
using namespace std;

int main()
{
	char *s1= "hello dong nice to meet you";
	char *s2 = "nice";
	char *s3 = strpbrk(s1,s2);//在源字符串（s1）中找出最先含有搜索字符串（s2）中任一字符的位置并返回，若找不到则返回空指针。
	if(s3)
		cout<<s3<<endl;
	else
		cout<<"NULL"<<endl;
} 
