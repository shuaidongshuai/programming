#include <iostream>
#include <string>
using namespace std;

class A{
public:
	A(){
		test();
	}
	virtual void test(){
		cout<<"A test"<<endl;
	}
};
class B:public A{
public:
	B(){
		test();		
	}
	virtual void test(){
		cout<<"B test"<<endl;
	}
};
int main(){
	B b;
}
