#include <iostream>
using namespace std;

typedef struct st_type
{
	int nCnt;
	int item[0];
}type_a;
//（有些编译器会报错无法编译可以改成：）
typedef struct st_type2
{
	int nCnt;
	int item[];
}type_a2;

void test()
{
	//int a[0];  在这里这样定义就是错的  在 gcc中可以，占4B
	//int a[];    同理
	cout << sizeof(type_a) << endl;
	cout << sizeof(type_a2) << endl;

	type_a *p = (type_a*)new char[sizeof(type_a) + 100 * sizeof(int)];
	type_a2 *p2 = (type_a2*)new char[sizeof(type_a2) + 100 * sizeof(int)];

	

	memcpy(p->item, "abcdefg", 8);//这样赋值是不行的
	memcpy(p2->item, "陈明东", 7);
	
	cout << p->item << endl;//这样是打印不出来的，因为是int类型
	cout << p2->item << endl;

	char *p3 = (char*)p->item;
	char *p4 = (char*)p2->item;
	
	cout << p3 << endl;
	cout << p4 << endl;

	cout << sizeof(type_a) << endl;
	cout << sizeof(type_a2) << endl;
}
int main()
{
	test();

	/*
	这样我们就产生了一个长为100的type_a类型的东西用p->item[n]就能简单地访问可变长元素，
	原理十分简单，分配了比sizeof(type_a)多的内存后int item[0]就有了其意义了，
	它指向的是int nCnt后面的内容，是没有内存需要的，而在分配时多分配的内存就可以由其来操控，
	是个十分好用的技巧。  
	*/

	getchar();
}
/*
C99允许。结构体最后使用0或1的长度数组的原因，主要是为了方便的管理内存缓冲区，
如果你直接使用指针而不使用数组，那么你在分配内存缓冲区时，就必须分配结构体一次，然后再分配结构体内的指针一次
（而此时分配的内存已经与结构体的内存不连续了，所以要分别管理即申请和释放）而如果使用数组，
那么只需要一次就可以全部分配出来，（见下面的例子），反过来，释放时也是一样，
使用数组，一次释放，使用指针，得先释放结构体内的指针，再释放结构体。还不能颠倒次序。
其实就是分配一段连续的的内存，减少内存的碎片化。


而释放同样简单：
C语言版：    free(p);
C++语言版：  delete []p;

优点有：
1.结构体无需分配新的存储变长数组的空间；
2.释放比较方便；
*/