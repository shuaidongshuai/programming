#include <iostream>
using namespace std; 

template<class T>
class A{
	public:
		T a;
		static int s;
};

//如果要对  类模板中的static 成员初始化。。需要这样 
template<class T>
int A<T>::s = 1; 

int main()
{
	A<int> a1;
	A<int> a2;
	
	A<char> b1;
	A<char> b2;
	
	a1.s++;
	b1.s += 48;
	
	cout<<a2.s<<endl;//我们可以看出。。a1  a2 公用一个static  int s
	
	cout<<b2.s<<endl;//我们可以看出。。a 系列和 b系列 用的不是一个static int s    因为c++编译器创建的是两个类，一个是int参数的，，一个是char参数的 
	
}
