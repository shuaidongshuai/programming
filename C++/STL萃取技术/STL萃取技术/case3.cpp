#include <iostream>
using namespace std;

template<class T>
struct MyIter
{
	typedef T value_type;
	T* ptr;
	MyIter(T* p = 0) :ptr(p){}
	T& operator*() const{ return *ptr; }
};

template <class I>
struct myiterator_traits
{
	typedef typename I::value_type value_type;
};
/*模板的偏特化  可以解决传来是内置类型*/
template<class T>
struct myiterator_traits<T*> 
{
	typedef T value_type;
};

template<class I>
typename myiterator_traits<I>::value_type func(I iter)
{
	return *iter;
}
int main()
{
	int *p = new int(6);
	MyIter<char> ite(new char('f'));
	cout << func(ite) << endl;
	cout << func(p) << endl;
	return 0;
}