#include <iostream>
#include <cstring>
using namespace std;

void test0()
{
	int a[] = { 1, 2, 3, 4, 5 };
	int *p = (int *)(&a + 1);				//前面(int *)根本不影响啥，本身就是int类型的数组
	printf("%d\n", *p);
	printf("%d\n", *(p - 1));
	printf("%d\n", *(p - 2));
	cout << "-------------------" << endl;
	p = (int *)(a + 1);
	printf("%d\n", *p);
	printf("%d\n", *(p - 1));
	printf("%d\n", *(p - 2));
	/*
	-858993460				5 的后一个肯定是垃圾值
	5
	4
	-------------------
	2
	1
	-858993460
	*/
	cout << "-------------------" << endl;
	cout << a << endl;
	cout << a + 1 << endl;	//这里步长为 4 
	cout << &a + 1 << endl;// 这里步长为 20 为什么是20呢？ 看下面
	/*
	0042F8C4	以这个地址为首地址，存储了5个int 也就占了20字节 = 0x14
	0042F8C8
	0042F8D8	刚好 0x80 = 0x6C + 0x14  也就是说数组名取地址之后  步长会发生变化 每次 + 1 步长都是数组大小
	*/
	cout << "-------------------" << endl;
	cout << a << endl;
	cout << (int *)&a + 1 << endl;	//这里步长为 4 
	/*
	0108F6A4
	0108F6A8	这里步长又变为了 4  因为：我们强转这个地址类型为 (int *)了
	*/
	cout << (int)a + 1 << endl; //如果变成了整形，步长肯定是1了
	/*
	0x108F6A5
	*/
}

void test1()
{
	int a[5] = { 1, 2, 3, 4, 5 };
	int *p1 = (int *)&a + 1;
	int *p2 = (int *)((int)a + 1);
	printf("%d,%d\n", p1[-1], *p2);//1,2000000
	// *p2肯定不是2  因为 (int)a 的步长变为了1 
	printf("%d\n", *(int *)((int)p2 - 1));
}

void test2()
{
	char a[] = "hello";
	cout << (void *)a << endl;
	cout << &a << endl;
	/*
	00FCF968
	00FCF968	地址都是一样  对数组名取地址，取的就是第一个字符的地址
	*/
	char *b = "hello";
	cout << (void *)b << endl;
	cout << &b << endl;
	/*
	0125E098
	0019F8CC	地址不一样    指针和数组不是一个概念，数组名只是一个偏移（是一个左值）
	*/
	int c[] = { 2, 3, 4, 5 };
	cout << (void *)c << endl;
	cout << &c << endl;
	/*
	0021FAB8
	0021FAB8	只要是数组，&c都是第一个数存储的地址，只需要注意“步长”就好了
	*/
}

void test3()
{
	unsigned char c = -1;
	int i = (int)c;
	printf("%d\n", c);//255   1字节最大就是255了

	c = -2;
	printf("%d\n", (int)c);//254
}

void test4()
{
	/*左移动都是 *2   右移动都是 /2 */
	int b = 0xff000000;
	b >>= 1;
	printf("%x\n", b);//ff800000    需要注意：负数右移最高位要补1
	//答案解析：  1111 1111 0000 后面全是0了，看前面几个就好了
	//右移1位后   1111 1111 1000 转换成16进制不就是 0xff800000

	/*想知道整形有多大么？？*/
	unsigned int i = 0xffffffff;
	i >>= 1;
	int ii = i;
	cout << ii << endl;		//这个就是int类型表示的最大值  也就是0x7fffffff   也就是0xffffffff >>= 1
	ii++;
	cout << ii << endl;		//超出一个就是负数的最大值了   负数最大也就是0xfffffff 也就是 -1 再加一就等于 0了
}

int main()
{
	test1();

	system("pause");
}