#include <iostream>
#include <string>
using namespace std;

class A{
public:
	void test(){
		cout<<"test A"<<endl;
	}
};
class B:public A{
public:
	void test(){
		cout<<"B test"<<endl;
	}
};

int main(){
	A *a = new B;
	a->test();
}
