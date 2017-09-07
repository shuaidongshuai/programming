#include<stdio.h>
int c ,a=4;
int dong(int a,int b)
{
	c=a*b;
	a=b-1;
	b++;
	return(a+b+1);
}
int main()
{
	int b=2,p=0;
	c=1; 
	p=dong(b, a);
	printf("%d,%d,%d,%d",a,b,c,p);
 } 
