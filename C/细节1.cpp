#include<iostream>
#include<cstdio>
using namespace std;

int main()
{
	char i = 128;//ascii码  范围在 0 - 127 
	unsigned int a = i;//先把 i 变为 int == -128  再把 int 变为 unsigned int (负数变 unsigned int 会非常大) 
	
	printf("%d\n",i); 
	printf("%u\n",a); 
	
	if(a==128)
	cout<<"yes"<<endl;
	else
	cout<<"no"<<endl;
}
