//#include <iostream>
//using namespace std;
////
////如果写成这样
////ostream operator << (ostream& os, Point& pt)
////则：
////Point a, b;
////cout << a << b;
////错误，只能写为：
////cout << a;
////cout << b;
////原因在于
////cout << a << b;
////相当于：
////(cout << a) << b;
////第一个()中返回cout的临时变量，它可以不可以作为左值。因而错误。
////
////如果写成：
////ostream& operator << (ostream& os, Point& pt)
////则：
////cout << a << b;
////正确，因为它等同于
////(cout << a) << b;
////(acout << a)返回cout的引用，即就是它自己，它可以再次作为左值。因而能够连着写这个输出流
//
//template < typename T >
//class A
//{
//    friend ostream &operator<< <T>(ostream &, const A< T > &);
//	friend A operator-<T>(A &a1, A &a2);
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
// };
//
//template < typename T >
//ostream &operator<< (ostream &output, const A< T > &a)
//{
//    output << "重载成功" << endl;
//    return output;
// }
//
//template<class T>
//A<T> operator-(A<T> &a1, A<T> &a2)
//{
//	A<T> tmp(a1.age - a2.age);
//	return tmp;
//}
//
//int main2()
//{
//	A<int> a;
//	cout << a << a;
//	cin.get();
//	return 0;
// }
//int main3()
//{
//	A<int> a(10);
//	A<int> b(50);
//	A<int> c = b - a;
//	c.show();
//
//
//	cin.get();
//	return 0;
//}