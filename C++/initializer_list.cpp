#include <iostream>
#include <vector>
#include <deque>
#include <typeinfo>
using namespace std;
/*
都知道C++11出现了一个列表初始化
如：int a{1};
*/ 
void test(){
	int a{1};
	char b[5]{1,2,3,4};
	vector<int> v{1,2,4};
	deque<int> d{7,8,9}; 
}
/*
对于内置类型的确是做了提升
但是对于很多类：vector/deque...来说怎么让{}适应自己呢？ 实质上是提供了一个 initializer_list 这么一个类
所有 { } 都会被隐式转化为 initializer_list
stl_vector.h里面 增加了构造函数 {1,2} 会被默认转化为一个 initializer_list 类 
vector(initializer_list<value_type> __l,
	     const allocator_type& __a = allocator_type())
      : _Base(__a)
      {
	_M_range_initialize(__l.begin(), __l.end(),
			    random_access_iterator_tag());
      }
构造函数里面就是循环{1,2,3}里面的值
*/

class B{
public:
	explicit B(int a, int b){cout<<a<<","<<b<<endl;}
	explicit B(initializer_list<int> __l){
		for(auto l : __l)
			cout<<l<<" ";
		cout<<endl;
	}
	B(const B &b){cout<<"copy B()"<<endl;} 
}; 
void test2(){
	B b1(1,2);
	B b2{1,2};
	B b3({1,2});
	B b4({1,2,3});
//	B b5 = {1,2}; converting to 'B' from initializer list would use explicit constructor 'B::B(std::initializer_list<int>)'
//	B b6 = {1,2,3};
} 
int main() {
	cout<<__cplusplus<<endl; 
	test();
	test2();
}
