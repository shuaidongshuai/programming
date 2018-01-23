#include<iostream>
#include <cstring>
using namespace std;

class A {
public:
	A() = default;
	A(const A &a) = default;
	~A() = default;
	A &operator=(A &a) = default;
//	const A *operator&() = default;
//	const A *operator&() const = default;
	
	A(A &&) = default;
	A &operator=(A &&a) = default;
};
template <typename T> 
void test(T a){
a = 432;
a = fdsa;
}
int main(){
	 
}
