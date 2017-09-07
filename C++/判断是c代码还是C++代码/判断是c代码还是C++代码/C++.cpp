#include <stdio.h>

extern "C"
{
	int test();
}

int main()
{
#ifdef __cplusplus
	printf("C++");
#else
	printf("C");
#endif

	printf("\n------------------------------------\n");


	test();

	getchar();
	return 0;
}