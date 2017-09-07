#include<iostream>
#include<string>
#include<cstring>//这个是为下面strlen函数准备的   和上面那个类string不一样
using namespace std;
void main()
{
	string a;
	char b[30];
	cout<<strlen(b)<<endl;//由于还没有定义  空字符出现的位置是随机的
	cout<<a.size()<<endl;
	cout<<sizeof(b)<<endl;
}
