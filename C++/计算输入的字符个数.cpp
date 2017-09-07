#include<iostream>
using namespace std;
int main()
{
	int i;
	char str[100],*p=str;
	cin>>str;
	while(*p)
	{
	p++;
	i++;
}
	cout<<p-str<<endl;
	cout<<i<<endl;
}
