#include<stdio.h>
int main()
{
	const int a = 10;

	*((int *)&a) = 1000;

	printf("%d", a);//c语言，弱类型。。只要自己想。const的值自己可以改

	getchar();
	return 0;
}