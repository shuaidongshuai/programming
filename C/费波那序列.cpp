#include<stdio.h>
int main()
{
	int i,a[100];
	for(i=2;i<100;i++)
	{
		a[1]=a[0]=1;
		a[i]=a[i-1]+a[i-2];
	}
	for(i=0;i<100;i++)
	printf("%d\n",a[i]);
}
