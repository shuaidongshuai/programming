#include<stdio.h>
int main()
{
	int a=0;
	a=1;
	goto err;
	a=2;
		printf("%d",a);
err:
	a=10;
		printf("%d",a);
 } 
