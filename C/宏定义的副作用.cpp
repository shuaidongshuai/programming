#include<stdio.h>
#define M(a,b) ( (a)<(b)?(a):(b) )

int dong(int a,int b)
{
	return a>b?a:b;
}

int main()
{
	int a = 1;
	int b = 2;
	int c = dong(a++,b);
	printf("a = %d\n",a);
	printf("b = %d\n",b);
	printf("c = %d\n",c);
	
	a=1;
	b=2;
	c = M(a++,b);
	printf("\na = %d\n",a);
	printf("b = %d\n",b);
	printf("c = %d\n",c);
	
	a=1;
	b=2; 
	c = (a++)<(b)?(a++):(b);
	printf("\na = %d\n",a);
	printf("b = %d\n",b);
	printf("c = %d\n",c);	
	
	return 0;
 } 
