#include<stdio.h>
int main()
{
	int t,i,a[10],*p,*q;
	for(i=0;i<10;i++)
	scanf("%d",&a[i]);
	for(p=a,q=a+9;p<a+5;p++,q--)
	{
		t=*p;
		*p=*q;
		*q=t;
	}
	for(i=0;i<10;i++)
	printf("%d  ",a[i]);
 } 
