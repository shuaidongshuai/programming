#include <iostream>
using namespace std;

int main(){
	short a = 0x1234;
	char *b = (char *)&a;//指向了a的起始地址 
	if(*b == 0x12)//如果起始地址为0x12说明是大端 
		cout<<"大端"<<endl;
	else if(*b == 0x34)
		cout<<"小端"<<endl; 
} 
