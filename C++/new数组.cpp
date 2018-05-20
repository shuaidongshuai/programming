#include <iostream>
using namespace std;
//new数组只能调用默认构造，但是利用定位new可以达到调用其他构造的作用
 
class A{
public:
	int a; 
    A(){ cout << "A()" << endl;}
    A(int a):a(a){ cout << "A(int a)" << endl; }
    ~A(){ cout << "~A()" << " a=" << a << endl; }
};

int main(){
	A *a = new A[10];
	A *tmp = a;
	for(int i = 0; i < 10; ++i)
		new (tmp++)A(2);
	delete[] a; 
}
