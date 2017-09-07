#include<iostream>
using namespace std;
 struct dong
{
	int a;
	char *d;
};
int main()
{
	struct dong cmd;
	cmd.a=10;
	cmd.d ="dongdong";
	cout<<cmd.a <<endl;
	cout<<cmd.d <<endl;		
}
