#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
void main()
{
	int num = 18;
	printf("%d,%o,%x,%u\n", num, num, num, num);

	char str[32];
	_itoa(num, str, 2);
	printf("%s", str);

	getchar();
}