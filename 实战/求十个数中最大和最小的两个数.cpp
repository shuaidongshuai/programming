#include<stdio.h>
int main()
{
	int max,min,*p,a[10],i;
	for(i=0;i<10;i++)
	scanf("%d",&a[i]);
	max=min=a[0];
	for(p=a+1;p<a+10;p++)
	{
		if(max<*p) max=*p;
		else if(min>*p) min=*p;
	}
	printf("max=%d,min=%d",max,min);
 } 
