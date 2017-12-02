#include <iostream> 
using namespace std;
class A
{
public:
	void test(){
		cout<<"test"<<endl;
	}
};
int main(){
	void(A::*Func)();
	Func = &A::test;
	A a; 
	(a.*Func)();
	return true;
}
