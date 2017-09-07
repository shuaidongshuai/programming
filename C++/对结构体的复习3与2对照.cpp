#include<iostream>
using namespace std;
typedef struct dong
{
	int a;
	char *d;
};
int main()
{
	dong cmd;
	cmd.a=10;
	cmd.d ="dongdong";
	cout<<cmd.a <<endl;
	cout<<cmd.d <<endl;		
}
