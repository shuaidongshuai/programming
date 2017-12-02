#include <iostream> 
using namespace std;
//class私有继承 
class A{
public:
	int a;	
};
class B: A{}; 
class C: B{};
//struct共有继承
struct A2{ int a; };
struct B2: A2{};
struct C2: B2{};

int main(){
	cout<<sizeof(C)<<endl;//4 虽然是私有继承，子类不能用，但是内存上还是得copy 
	cout<<sizeof(C2)<<endl;//4
//	C().a;	编译都不通过 
	C2().a;
}
