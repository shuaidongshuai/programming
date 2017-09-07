#include<stdio.h>
int main()
{
	int a,b,c,d,e,x;
	scanf("%d",&x);
	a=x/10000;
	b=x%10000/1000;
	c=x%1000/100;
	d=x%100/10;
	e=x%10;
	if(a!=0) printf("there are 5  %d%d%d%d%d",e,d,c,b,a);
	else if(b!=0) printf("there are 4  %d%d%d%d",e,d,c,b);
	else if(c!=0) printf("there are 3  %d%d%d",e,d,c);
	else if(d!=0) printf("there are 2  %d%d",e,d);
	else if(e!=0) printf("there are 1  %d",e);
 } 
