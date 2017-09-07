#include <stdio.h>
int test()
{
#ifdef __cplusplus
	printf("C++");
#else
	printf("C");
#endif
	getchar();
	return 0;
}