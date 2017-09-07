#include<stdio.h>
int dong(int x)
{
	int z;
	z=x*x*x;
	return z;
 } 
 int d(int y)
 {
 	int z;
 	z=y*y*y;
 	return z; 
 }
 int main()
 {
 	int a,b,c;
 	scanf("%d,%d",&a,&b);
 	c=dong(a)+d(b);
 	printf("%d",c);
 }
