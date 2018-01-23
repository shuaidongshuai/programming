#include<iostream>
#include <cstring>
using namespace std;

#define varArg int
varArg Add(varArg a, varArg b){
	return a + b;
}

void test(){
	short a = 10, b = 20;
//สนำร
	#undef varArg
	#define varArg short
	short c = Add(a, b);
	cout<<c<<endl; 
} 

int main(){
	test();
}
