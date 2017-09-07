#include <iostream> 
using namespace std;

class A
{
public:	
	virtual void func(){
		cout<<"AAAAAAAA"<<endl;
	}
};

class B:public A
{
private:
	void func(){
		cout<<"BBBBBBB"<<endl;
	}	
};

int main()
{
	A *a = new B;
	a->func();
}
