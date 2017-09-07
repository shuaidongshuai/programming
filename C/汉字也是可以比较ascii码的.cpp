#include <iostream> 
using namespace std;

int main()
{
	char a[] = "陈";
	char b[] = "东";
	char c[] = "飞";
	
	if(a[0]<b[0])
	{
		cout<<b<<" 大于 "<<a<<endl;
	}
	
	if(c[0]>b[0])
	{
		cout<<c<<" 大于 "<<b<<endl;
	}
	
	if(a[0]<c[0])
	{
		cout<<c<<" 大于 "<<a<<endl;
	}

	
}
