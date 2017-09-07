#include<iostream>
using namespace std;

template<class T>
struct MyIter{
	typedef T value_type;
	T* ptr;
	MyIter(T* p = 0) :ptr(p){}
	T& operator*() const{ return *ptr; }
};

template<class I>
typename I::value_type func(I iter)//把T指向的类型给萃取出来
{
	return *iter;
}
int main2()
{
	MyIter<int> ite(new int(8));
	cout << func(ite) << endl;
	system("pause");
	return 0;
}