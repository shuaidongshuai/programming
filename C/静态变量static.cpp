#include<stdio.h>
int dong(int a)
{
	static int c;
	c=a;		
	c++;
	return c;
}
int main()
{
	int b=1,c,d,e;
	d=dong(b);
	e=dong(d);	
	printf("%d  %d\n",d,e);
}
