#include <iostream>
using namespace std;

/*
有没有发现 v2 = v; 又会copy一次？ 但是我们可能是想他们两共享一片内存
所以就写一个MyVector的类  就是对vector的包装
*/
void test1();
/*
test2就没有多余的拷贝构造
*/
void test2();

int main()
{
	//test1();
	test2();

	system("pause");
	return 0;
}