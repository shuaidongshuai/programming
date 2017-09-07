#include <iostream>
#include <string>
using namespace std;

struct A
{
	int a;
	struct A *next;	
};

int main()
{
	cout<<&((struct A*)0)->next<<endl;
	return 0;
}

