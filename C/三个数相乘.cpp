#include<stdio.h>
int dong(int x,int y,int z)
{
	int r;
	r=x*y*z;
}
int main()
{
	int a,b,c,d;
	scanf("%d,%d,%d",&a,&b,&c);
	d=dong(a,b,c);
	printf("½á¹ûÊÇ£º%d",d); 
}
