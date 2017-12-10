#include <iostream>
using namespace std;

class B{
public:
	B(int a = 0){cout<<"B()"<<endl;}
	B &operator+=(const B &b){
		 cout<<"operator +="<<endl; 
		 return *this;
	}
	~B(){cout<<"~B()"<<endl;}
};
void test(){
	B b;
	b += 2;//先把2隐式转化为B 然后再相加 注：前提是有对应的构造函数
		//构造 和 += 其中一个前面加 explicit 那就编译不过 
}
/*
B()
B()
operator +=
~B()
~B()
*/
int main() {
	test();
}
