#include <iostream>
#include <type_traits>
using namespace std;

template<typename T>
void print(){
	cout << "is_array:" << is_array<T>::value << endl;
	cout << "is_class:" << is_class<T>::value << endl;
	cout << "is_enum:" << is_enum<T>::value << endl;
	cout << "is_function:" << is_function<T>::value << endl;
	cout << "is_integral:" << is_integral<T>::value << endl;
	cout << "is_lvalue_reference:" << is_lvalue_reference<T>::value << endl;
	cout << "is_pointer:" << is_pointer<T>::value << endl;
	cout << "is_union:" << is_union<T>::value << endl;
	cout << "is_void:" << is_void<T>::value << endl;
	cout << "虚析构函数 有么:" << has_virtual_destructor<T>::value << endl;
	cout << "赋值 不重要:" << is_trivially_assignable<T, T>::value << endl;
	cout << "构造 不重要:" << is_trivially_constructible<T>::value << endl;
	cout << "拷贝赋值 不重要:" << is_trivially_copy_assignable<T>::value << endl;
	cout << "拷贝构造 不重要:" << is_trivially_copy_constructible<T>::value << endl;
	cout << "默认析构 不重要:" << is_trivially_destructible<T>::value << endl;
	cout << "默认构造 不重要:" << is_trivially_default_constructible<T>::value << endl;
	cout << "move 赋值 不重要:" << is_trivially_move_assignable<T>::value << endl;
	cout << "move 构造 不重要:" << is_trivially_move_constructible<T>::value << endl;
	cout << "move 构造 有么:" << is_move_constructible<T>::value << endl;
	cout << "move 赋值 有么:" << is_move_assignable<T>::value << endl;
}
class A{
};
class B{
public:
	B(){}
	~B() = delete;
	B(const B &) = delete;
};
class C{
public:
	C(){ cout << "b" << endl; }
	virtual ~C(){}
	C(const C &) = default;//默认就是有copy构造，写不写一样 
	C(C &&) = delete;
	C &operator=(C &&) = delete;
};
int main(){
	cout << "-----------int---------------" << endl;
	print<int>();
	cout << "------------B--------------" << endl;
	print<A>();
	cout << "-----B(){} ~B()=delete; B(const B &)=delete;-----" << endl;
	print<B>();
	cout << "----C(){ cout }  virtual ~C(){}-----------" << endl;
	print<C>();
	getchar();
	return 0;
}
/*
-----------int---------------
-----------int---------------
-----------int---------------
is_array:0
is_class:0
is_enum:0
is_function:0
is_integral:1
is_lvalue_reference:0
is_pointer:0
is_union:0
is_void:0
虚析构函数 有么:0
赋值 不重要:0
构造 不重要:1
拷贝赋值 不重要:1
拷贝构造 不重要:1
默认析构 不重要:1
默认构造 不重要:1
move 赋值 不重要:1
move 构造 不重要:1
move 构造 有么:1
move 赋值 有么:1
------------B--------------
is_array:0
is_class:1
is_enum:0
is_function:0
is_integral:0
is_lvalue_reference:0
is_pointer:0
is_union:0
is_void:0
虚析构函数 有么:0
赋值 不重要:1
构造 不重要:1
拷贝赋值 不重要:1
拷贝构造 不重要:1
默认析构 不重要:1
默认构造 不重要:1
move 赋值 不重要:1
move 构造 不重要:1
move 构造 有么:1
move 赋值 有么:1
-----B(){} ~B()=delete; B(const B &)=delete;-----
is_array:0
is_class:1
is_enum:0
is_function:0
is_integral:0
is_lvalue_reference:0
is_pointer:0
is_union:0
is_void:0
虚析构函数 有么:0
赋值 不重要:1
构造 不重要:0
拷贝赋值 不重要:1
拷贝构造 不重要:0
默认析构 不重要:0
默认构造 不重要:0
move 赋值 不重要:1
move 构造 不重要:0
move 构造 有么:1
move 赋值 有么:1
----C(){ cout }  virtual ~C(){}--C(C &&) = delete; ---------
is_array:0
is_class:1
is_enum:0
is_function:0
is_integral:0
is_lvalue_reference:0
is_pointer:0
is_union:0
is_void:0
虚析构函数 有么:1
赋值 不重要:0
构造 不重要:0
拷贝赋值 不重要:0
拷贝构造 不重要:0
默认析构 不重要:0
默认构造 不重要:0
move 赋值 不重要:0
move 构造 不重要:0
move 构造 有么:1	//这个地方和官网不一样，官网上是0，因为自己delete了 
move 赋值 有么:1	//同上 
*/ 
