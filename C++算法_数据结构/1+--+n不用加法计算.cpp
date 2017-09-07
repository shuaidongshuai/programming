/*
题目：
不能用* / for while if else switch case ?:
来计算 1 + -- + n
*/
#include <iostream>
using namespace std;
/////////////////////////////////////////////////////////////
/* 方法一 利用构造函数求解 */
class A
{
	static int sum;
	static int cur;
public:
	A()
	{
		++cur;
		sum += cur;
	}
	int getSum(){return sum;}
};
int A::sum = 0;
int A::cur = 0;
void res1(int n)
{
	A *a = new A[n];			/* C++只有构造函数可以不用循环判断语句指定调用的次数 */
	cout<<a->getSum()<<endl;
}
/////////////////////////////////////////////////////////////
/* 方法二 利用虚函数求解 */
class B;
B *b[2];

class B
{
public:
	virtual int count(int n){return 0;}
};
class BB:public B
{
public:
	int count(int n)
	{
		return b[!!n]->count(n-1) + n;
	}
};
void res2(int n)
{
	b[0] = new B;
	b[1] = new BB;
	cout<< b[1]->count(n) <<endl;
	delete b[0];
	delete b[1];
}
/* 没用递归是因为递归结束的条件一般都要用if语句	但是上面这种方法用虚函数来控制结束条件 */
/////////////////////////////////////////////////////////////
/* 方法三 利用函数指针求解 和上面虚函数类似 */
typedef int (*f)(int n); 
int over(int n){return 0;}
int count(int n)
{
	static f func[2] = {over,count};
	return func[!!n](n - 1) + n;
}
void res3(int n)
{
	cout<< count(n) <<endl;
}
/////////////////////////////////////////////////////////////
/* 方法四 利用模板 简单 but 必须在编译期决定n值 不能动态输入 而且n不能太大*/
template<int N>
class C
{
public:
	enum value{val = C<N - 1>::val + N};
};
template<>
class C<1>
{
public:
	enum value{val = 1};
};
void res4()
{
	cout<<C<100>::val<<endl;
}

int main()
{
	res1(100);
	res2(100);
	res3(100);
	res4();
}
