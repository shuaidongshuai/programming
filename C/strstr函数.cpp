#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	char *a = "www.baidu.com/dong.html";
	char *b = ".com";
	char *c = strstr(a,b); 
	cout<<c<<endl;
	c = strstr(a,"dng");//Ã»ÕÒµ½·µ»Ø¿Õ 
	if(c == NULL)
		cout<<"NULL"<<endl;
	else
		cout<<c<<endl;
}


