#include <iostream>
using namespace std;
class a
{
	int arr[20];
	virtual void test();
};
class b :public virtual a
{
	/*这里会吧a中的arr[20]和vptr指针  都继承过来*/
	int bb;
	/*下面函数只产生一个指针*/
	virtual void fff();
	virtual void ggg();
	virtual void hhh();
};

void test7()
{
	cout << sizeof(a) << endl;
	cout << sizeof(b) << endl;
	cout << "-------------------------------------" << endl;
}

/*
84
96
*/