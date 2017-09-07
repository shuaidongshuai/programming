#include <stdio.h>
#include <stdlib.h>

long long z = 10;
short x = 10;
int y = 10;
char c = 10;

int main()
{
	printf("%d  %d  %d\n", sizeof(int), sizeof(short), sizeof(long long));
	printf("z 0x%x\n", &z);
	printf("x 0x%x\n", &x);
	printf("y 0x%x\n", &y);
	printf("c 0x%x\n", &c);

	system("pause");
}
/*
4  2  8
z 0x10f8040
x 0x10f8048		+ 8
y 0x10f804c		+ 4		short在vs2013中分配的是4个字节★★★★求解：微软为什么这么做
c 0x10f804a		+ 4
*/
