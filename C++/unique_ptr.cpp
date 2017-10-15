#include <iostream>
#include <vector>
#include <memory>//智能指针在这个头文件里 
using namespace std;

class A{
public:
	int a; 
	A(){cout<<"A"<<endl;}
	~A(){cout<<"~A"<<endl;}
};

void test1(){
	unique_ptr<int> up(new int(4));
//	int *p2 = up;	不能赋值 
	int *p1 = up.release(); //但是释放所有权  后 可以赋值  
}
void test2(){
	unique_ptr<A> u_s(new A);  
	u_s=nullptr;//显式销毁所指对象，同时智能指针变为空指针。与u_s.reset()等价  
	cout<<"test2"<<endl;
}
/*
A
~A
test2
*/
void test3(){
	unique_ptr<A> u_s(new A); 
	unique_ptr<A> u_s2 = std::move(u_s); //所有权转移(通过移动语义)，u_s所有权转移后，变成“空指针” ，但是不析构 
	cout<<"test3"<<endl;
//	u_s->a = 1;	已经变为NULL了 
}
/*
A
test3
~A
*/
unique_ptr<A> test4(){
	unique_ptr<A> up(new A); 
	return up;//自动调用move语义 
}
void test5(){
	cout<<"test5"<<endl;
	unique_ptr<A> u_a = test4();
}
/*
test5
A
~A
*/ 
void test6(){
	unique_ptr<A[]> up(new A[2]); //unique_ptr可以指向数组  默认析构有delete 和 delete[] 
}
//可放在容器中(弥补了auto_ptr不能作为容器元素的缺点)
void test7(){
	vector<unique_ptr<A>>v;  
	unique_ptr<A> p1(new A);  
	v.push_back(std::move(p1));//但是需要用move语义 
}
int main(){
//	test2();
//	test3();
//	test5();
//	test6();
	test7();
} 
