#include <iostream>
#include <typeinfo>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

class A{
public:
	A(){
		cout<<"A"<<endl;
	}
};
class B{
public:
	vector<A> v;
	B(int i):v(i){
	}
};

int main(){
	B b(3);
}
/*
Dello dong
Dello dong
Hello dong
hello dong
*/ 
