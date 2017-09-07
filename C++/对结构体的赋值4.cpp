#include<iostream>
using namespace std;
struct dong				//如果下面想要用cmd.a   .b  这前面就不能加typedef   加了  就相当与  struct dong ==cmd 
{
	int a;
	char *d;
}cmd;
int main()
{
	cmd.a=10;
	cmd.d ="dongdong";
	cout<<cmd.a <<endl;
	cout<<cmd.d <<endl;		
}
