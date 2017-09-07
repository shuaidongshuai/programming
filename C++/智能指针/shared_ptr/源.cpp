#include <iostream>
#include <memory>
using namespace std;

class A
{
public:
	A(){ cout << "构造" << endl; }
	~A(){ cout << "析构" << endl; }
	void show(){ cout << "show" << endl; }
};
void test1()
{
	int *p = new int(10);
	shared_ptr<int> ptr(p);
	cout << *ptr << " " << *p << endl;
}
/*下面两种方法都是一样的*/
void test2()
{
	shared_ptr<A> ptr(new A);
	ptr->show();
}
/*
构造
show
析构
*/
void test3()
{
	shared_ptr<A> ptr = make_shared<A>();
	ptr->show();
}
/*
构造
show
析构
*/
void test4()
{
	shared_ptr<A> ptr(new A);
	shared_ptr<A> ptr2(ptr);
	ptr->show();
	ptr2->show();
}
/*
构造
show
show
析构
*/
void test5()
{
	A *p = new A;
	shared_ptr<A> ptr(p);
	shared_ptr<A> ptr2(p);//这样程序会直接挂掉。两次释放同一片内存，所以我们最好不要出现指针，全用智能指针
}
int main()
{
	test5();

	system("pause");
	return 0;
}