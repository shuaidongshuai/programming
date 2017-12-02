#include <iostream> 
#include <typeinfo>
using namespace std;
class A{
public:
	virtual void test(){}
};
class B : public A{
public:
};
int main(){
	int i = 0;
	++i;
	i++;
	getchar();
}
/*
class A *
class B
*/