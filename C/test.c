#include <stdio.h>

extern inline int test()
{
	return 1;
}
int main()
{
	printf("%d",test());
	
	return 0;
}

