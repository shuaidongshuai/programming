#include <stdio.h>
int main99()
{
	int a = 10;
	const int c = a;	// int -> const int  可行

	const int Pi = 3;
	int i = Pi;			// const int -> int 也行
	i = 5;
	printf("%d", i);

	//const int a = 10;
	//const int &b = a;	//	const int -> const int 

	getchar();
	return 0;
}