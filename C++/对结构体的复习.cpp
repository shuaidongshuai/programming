#include<iostream>
#include<cstdlib> 
using namespace std;
typedef struct dong
{
	int a;
	char *d;
}cmd;
cmd *chen()
{
	cmd *c;
	c=(cmd *)malloc(sizeof(cmd));
	c->a=10;
	c->d="asfdsad";
	return c;
}
void print(cmd *p)
{
	cout<<p->a <<endl;
	cout<<p->d <<endl;
}
int main()
{
	cmd *m;
	m=chen();
	print(m);
	return 0;
}
