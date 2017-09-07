#include <iostream>
using namespace std;
//要在vs中调试 

//想要在A 中声明一个带模板的友元函数，，必须在类前面加上   类  和 函数 的声明
template<class T>
class A;

template<class T>
void sub(A<T> &a, int i);

template<class T>
A<T> operator+(A<T> &a1, A<T> &a2);

template < typename T >
class A
{
	friend A operator-<T>(A &a1, A &a2);
	friend A operator+<T>(A &a1, A &a2);
	friend void add(A<int> &, int);//友元函数，，外部的友元，，和这个类没有任何关系只是，友元函数可以访问这个类中的任何东西 
	friend void sub<T>(A &, int);//带模板的友元函数
	T age;
public:
	A(){}
	A(T a)
	{
		age = a;
	}
	void show()
	{
		cout << age << endl;
	}
};

template<class T>
A<T> operator-(A<T> &a1, A<T> &a2)
{
	A<T> tmp(a1.age - a2.age);
	return tmp;
}

void add(A<int> &a, int i)
{
	a.age += i;
	//cout << "hello" << endl;
}

template<class T>
A<T> operator+(A<T> &a1, A<T> &a2)//这个函数必须在 add函数之前实现。。不然就报错。。不知道这是为什么
{								//也可以吧这个函数放在add函数之后，但是必须在类前，进行函数声明
	A<T> tmp(a1.age + a2.age);//猜测：不能放在add后面的原因在于内存中已经有了<int>的类了，所以之后不会再创建A类，但是之前的A类并不认识+这个符号
	return tmp;				//就像，不认识 sub 这个符号一样，需要在类前面进行函数声明，让类知道有这个类
}							//发现：只要add函数不对A类有任何动作，那么就不会出现 不认识 + 这个符号，还是相当于

template<class T>
void sub(A<T> &a, int i)
{
	A<T> c(a.age - i);
	a.age = c.age;
}

int main11()
{
	A<int> a(10);
	A<int> b(50);
	A<int> c = b - a;
	c.show();

	A<int>d = b + a;
	d.show();

	cin.get();
	return 0;
}

int main22()
{
	A<int> a(10);
	add(a, 1000);
	a.show();

	sub(a, 20);
	a.show();

	cin.get();
	return 0;
}

int main()
{
	A<int> a(10);
	add(a, 1000);
	a.show();

	sub(a, 20);
	a.show();

	A<int> b(50);
	A<int> c = b - a;
	c.show();

	A<int>d = b + a;
	d.show();


	cin.get();
	return 0;
}
