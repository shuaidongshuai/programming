#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct{
	char val;
}Node, *Tree;
Node* a = new Node;

//我们可以改变地址上的值，但是不能改变传进来的  变量的地址
void test1(Tree t)//千万注意啊，，这里有一个拷贝，，以前一直以为指针就不拷贝了，，其实任何东西她都拷贝了，，相当于 Tree t = p;
{
	cout <<t<< endl;

	t = a;

	cout << t << endl;
}
//我们可以改变地址上的值，也能改变传进来的  变量的地址
void test2(Tree &t)//只有引用，才是传进来的东西，没有任何改变
{
	cout << t << endl;

	t = a;

	cout << t << endl;
}

int main2()
{
	Tree p = new Node;
	test1(p);
	cout << p << endl;

	cout << "-------------------" << endl;

	test2(p);
	cout << p << endl;

	cin.get();
	return 0;
}