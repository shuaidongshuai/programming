#include <stdio.h>
#include <iostream>
using namespace std;

char *test()
{
	char str[] = "hello";
	return str;
} 

int main()
{
	char *p = test();
	//printf("%s",p);
	cout<<p<<endl;
}

