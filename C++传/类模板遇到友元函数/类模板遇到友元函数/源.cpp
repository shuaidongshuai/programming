//#include <iostream>
//using namespace std;
//
//template < typename T >
//class A
//{
//	friend A operator+<T>(A &a1, A &a2);
//	friend void add(A<int> &, int);
//	T age;
//public:
//	A(){}
//	A(T a)
//	{
//		age = a;
//	}
//	void show()
//	{
//		cout << age << endl;
//	}
//};
//
//void add(A<int> &a, int i)
//{
//	a.age += i;
//}
//
//template<class T>
//A<T> operator+(A<T> &a1, A<T> &a2)
//{
//	A<T> tmp(a1.age + a2.age);
//	return tmp;
//}
//
//int main()
//{
//		A<int> a(10);
//		add(a, 1000);
//		a.show();
//
//		A<int> b(50);
//	
//		A<int>d = b + a;
//		d.show();
//	
//	cin.get();
//	return 0;
//}