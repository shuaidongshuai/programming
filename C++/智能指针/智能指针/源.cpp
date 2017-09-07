#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

void test1()
{
	//只能指针主要解决内存泄漏问题
	//int* p = new int[1024 * 1024 * 100];//直接占400M 内存。因为申请是以页申请的，所以不是100M

	//只能用构造函数初始化 不能用 = 
	auto_ptr<int> p1(new int[1024 * 1024 * 100]);//只占了  0.4M 
}
void test2()
{
	/*
	中断：
	智能指针不能new STL类库中的类
	原因：auto_ptr 会不断的节约内存，不断delete，会导致string类内部错误
	*/
}
void test3()
{
	//STL 包含 auto_ptr 可以
	vector<auto_ptr<int>> vp;
	vp.push_back(auto_ptr<int>(new int[10]));
	//vector容器中有一个auto_ptr 这个auto_ptr指向一个整型数组内存
}
void test4()
{
	char *p = "hello";
	auto_ptr<char *> p1(&p);
	
	auto_ptr<char *> p2(p1);		//在创建p2的时候p1会被析构

	auto_ptr<char *> p3(&p);
	auto_ptr<char *> p4 = p3;		//在创建p4的时候p3会被析构

	//同时运行p1 p2    p1中断
	/*cout << "p2----" << *p2 << endl;
	cout << "p1----" << *p1 << endl;*/

	//同时运行p3 p4  p3中断
	cout << "p4-----" << *p4 << endl;
	cout << "p3----" << *p3 << endl;
	
	
	/*
	问题：
	当我们打印p2的时候还没有什么问题，但是当我们打印p3的时候中断了

	虽然是浅拷贝，但是不是单纯的浅拷贝。
	浅拷贝中有一个引用计数，当引用计数为0 就真正的delete内存
	
	5. 防止两个auto_ptr对象拥有同一个对象（一块内存）
	因为auto_ptr的所有权独有-----------------------------如果用了 = 那么等号右边的智能指针将会被析构
	
	*/
}


