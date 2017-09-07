#include <stdio.h>
#include <stdlib.h>
void dong7()
{
	printf("基类  dong1\n");
}
void dong8()
{
	printf("基类  dong2\n");
}
void dong9()
{
	printf("基类  dong3\n");
}
//模拟虚表结构
typedef struct
{
	void(*v1)();
}AA;

//模拟一个类中的虚表
AA test1 = { &dong7};
typedef struct A
{
	//int b;	//尝试一下解注释，如果B类只有4字节大小，A有8字节，B强转为A，也只能操作前4字节的东西，操作下面这个指针将会  栈溢出
	void *vptr;//虚函数指针   占4字节
}A;


typedef struct
{
	void(*v1)();
	void(*v2)();
	void(*v3)();
}BB;
BB test2 = { &dong7, &dong8, dong9 };
typedef struct B
{
	//void *vptr;//虚函数指针
	//A a;//终于知道为什么demo里面要加上A a   目的：为了确保B类比A类大，到时候创建B然后赋给A\
				B类就可以操作A类中的元素了，如果B类于A，就会发现stack溢出(如果操作A中偏移地址超过B最大偏移地址)
	int a;//让B大小为4字节
}B;
int main3()
{
	/*A a;
	B* b = (B*)&a;
	b->vptr = &test2;
	((BB*)(b->vptr))->v1();
	((BB*)(b->vptr))->v2();*/
	printf("%d", sizeof(B));
	printf("%d", sizeof(A));
	B b;
	A *a = (A*)&b;//这里是关键。虽然创建的是b，但是可以强转为A，目的在于利用A中的指针
	a->vptr = &test2;//a中的指针可以指向  a  b  任何一个结构体
	((BB*)(a->vptr))->v1();
	((BB*)(a->vptr))->v2();
	((AA*)(a->vptr))->v1();


	system("pause");
	return 0;
}