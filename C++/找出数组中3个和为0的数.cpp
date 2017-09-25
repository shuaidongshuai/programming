#include<iostream>
using namespace std;

class A
{
public:
	int a;
	A(int a){
	} 
	void show() const ;
	void go(){
		show();
	}
};
void A::show() const {
	cout<<"show"<<endl;
}
int main()
{
	A a(2);
	a.go();
}

